#include <iostream>
#include <vector>
using namespace std;

const int N = 7;
int Gr[N][N];     // список смежности
int A[N] = {0};

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

void Graph() {
    Gr[0][1] = 1;
    Gr[0][2] = 1;
    Gr[0][4] = 1;
    Gr[0][5] = 1;
    Gr[1][0] = 1;
    Gr[1][3] = 1;
    Gr[2][0] = 1;
    Gr[2][5] = 1;
    Gr[3][1] = 1;
    Gr[4][0] = 1;
    Gr[4][6] = 1;
    Gr[5][0] = 1;
    Gr[5][2] = 1;
    Gr[5][6] = 1;
    Gr[6][4] = 1;
    Gr[6][5] = 1;
}

void glubina(int x){
    stack *head = NULL; //создаём стек  // 0 - не посещена, 1 - посещена
    A[x] = 1; //помечаем вершину x как посещенную
    push_stack(head, x);
    while (head) {
        bool f1 =  false;              
        x = head->inf;
        int y;
        for (int i = 0; i < N; i++) {
            // если существует непосещенная вершина, смежная x (A[Gr[x][i]] == 0)
            if (Gr[x][i] == 1 && A[i] == 0) {
                y = i;
                f1 = true;
                break;
            }
        }
        if (f1 == true){
            A[y] = 1;
            push_stack(head, y);
        }
        else {
            pop_stack(head);
        }     
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        if (A[i] == 0) {
            glubina(i);          // вызываем алгоритм для непосещенной вершины
        }
    }
}

void print_graph() {
    cout << "Список смежности" << endl;
    for (int i = 0; i < N; i++) { 
        cout << i; // вершина
        for (int j = 0; j < N; j++) {
            if (Gr[i][j] == 1){
                cout << " -> " << j;
            }
        }
        cout << endl;
    }
}

int main(){
    setlocale(LC_ALL,"RUS");
    Graph();
    print_graph();
    glubina(0);
    bool flag = true;
    for (int i = 0; i < N; i++){
        if (A[i] == 0){
            cout << "Граф несвязный";
            flag = false;
            break;
        }
    }
    if (flag){
        cout << "Граф связный";
    }
    return 0;
}