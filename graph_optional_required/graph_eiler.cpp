#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;


const int N = 7;
int Gr[N][N];     // список смежности
int sizeGr[N] = {0};

struct stack {
    int inf;
    stack *next;
};

void push_stack(stack *&h, int x) {
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop_stack(stack *&h) {
    int i = h->inf;
    stack *r = h;
    h = h->next;
    delete r;
    return i;
}


int printStack(stack *h) {
    int count_stack = 0; //счётчик
    stack *temp = NULL;
    stack *current = h;
    if (h == NULL){ // если элементов нет 
        cout << setw(15) <<  "empty";
        return 5;
    }
    while (current) {
        push_stack(temp, current->inf);
        current = current->next;
    }
    while (temp) {
        cout << pop_stack(temp) << " ";
        count_stack += 2;
    }
    return count_stack; // для setw
}


void Graph() {
    for (int i = 0; i < N; i++) {
        sizeGr[i] = 0;
    }
    Gr[0][sizeGr[0]++] = 1; // для 0
    Gr[0][sizeGr[0]++] = 2;
    Gr[0][sizeGr[0]++] = 4;
    Gr[0][sizeGr[0]++] = 5;
    Gr[1][sizeGr[1]++] = 0; // для 1
    Gr[1][sizeGr[1]++] = 3;
    Gr[2][sizeGr[2]++] = 0;// для 2
    Gr[2][sizeGr[2]++] = 5;
    Gr[3][sizeGr[3]++] = 1;// для 3
    Gr[4][sizeGr[4]++] = 0;// для 4
    Gr[4][sizeGr[4]++] = 6;
    Gr[5][sizeGr[5]++] = 0;// для 5
    Gr[5][sizeGr[5]++] = 2;
    Gr[5][sizeGr[5]++] = 6;
    Gr[6][sizeGr[6]++] = 4; // для 6
    Gr[6][sizeGr[6]++] = 5;
}

bool glubina(int x) {
    stack *head = NULL;
    int A[N] = {0};
    A[x] = 1;
    push_stack(head, x);
    while (head) {
        int v = head->inf;
        bool found = false;
        for (int i = 0; i < sizeGr[v]; ++i) {
            int y = Gr[v][i];
            if (!A[y]) {
                A[y] = 1;
                push_stack(head, y);
                found = true;
                break;
            }
        }
        if (!found) {
            pop_stack(head);
        }
    }
    for (int i = 0; i < N; ++i) {
        if (sizeGr[i] > 0 && A[i] == 0)
            return false;
    }
    return true;
}

void print_graph() {
    cout << "Список смежности" << endl;
    for (int i = 0; i < N; i++) { 
        cout << i << " -> "; //вершина
        for (int j = 0; j < sizeGr[i]; j++) {
            cout << Gr[i][j]; //её смежные
            if (j < sizeGr[i] - 1) cout << " -> ";
        }
        cout << endl;
    }
    cout << endl;
}

void eiler() {
    vector<list<int>> adj(N);
    int edges = 0;
    for (int v = 0; v < N; ++v) {
        for (int i = 0; i < sizeGr[v]; ++i) {
            int u = Gr[v][i];
            if (v <= u) {
                adj[v].push_back(u);
                adj[u].push_back(v);
                ++edges;
            }
        }
    }
    vector<int> odd;
    for (int v = 0; v < N; ++v) {
        if (adj[v].size() % 2 == 1)
            odd.push_back(v);
    }
    if (odd.size() != 0 && odd.size() != 2) {
        cout << "Количество нечётных вершин не 0 и не 2" << endl;
        return;
    }
    int x = -1;
    if (odd.size() == 2) {
        x = odd[0];
    } 
    else {
        for (int v = 0; v < N; ++v) {
            if (!adj[v].empty()) {
                x = v;
                break;
            }
        }
    }
    if (!glubina(x)) {
        cout << "Граф несвязный" << endl;
        return;
    }
    bool dop_edge = (odd.size() == 2);
    int dop_V1 = -1, dop_V2 = -1;
    if (dop_edge) {
        dop_V1 = odd[0];
        dop_V2 = odd[1];
        adj[dop_V1].push_back(dop_V2);
        adj[dop_V2].push_back(dop_V1);
    }
    stack *p = NULL;
    vector<int> res;
    push_stack(p, x);
    while (p) {
        int v = p->inf;
        if (!adj[v].empty()) {
            int u = adj[v].front();
            adj[v].pop_front();
            adj[u].remove(v);
            push_stack(p, u);
        } else {
            res.push_back(pop_stack(p));
        }
    }
    reverse(res.begin(), res.end());
    if (dop_edge) {
        int idx = -1;
        for (size_t i = 0; i + 1 < res.size(); ++i) {
            if ((res[i] == dop_V1 && res[i+1] == dop_V2) || (res[i] == dop_V2 && res[i+1] == dop_V1)) {
                idx = i;
                break;
            }
        }
        if (idx != -1) {
            vector<int> newRes;
            for (size_t i = idx + 1; i < res.size(); ++i)
                newRes.push_back(res[i]);
            // часть от 1 до idx
            for (int i = 1; i <= idx; ++i)
                newRes.push_back(res[i]);
            res = move(newRes);
        }
    }
    for (size_t i = 0; i < res.size(); ++i) {
        cout << res[i];
        if (i + 1 < res.size()) cout << " -> ";
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    Graph();
    print_graph();
    cout << "Эйлеров путь" << endl;
    eiler();
    return 0;
}