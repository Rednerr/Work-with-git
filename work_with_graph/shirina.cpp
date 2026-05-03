#include <iostream>
#include <vector>
using namespace std;


const int N = 7;
int Gr[N][N];     // список смежности

struct queue{
    int inf;
    queue *next;
};
  
void push_queue(queue *&h,queue *&t, int x){ 
    queue *r = new queue;
    r->inf=x;
    r->next=NULL;
    if (!h && !t){ 
        h=t=r;
    }
    else{  
        t->next=r; 
        t=r;    
    }
}

int pop_queue(queue *&h,queue *&t){
    queue *r = h; 
    int i = h->inf; 
    h = h->next; 
    if (!h){
        t = NULL;
    }
    delete r; 
    return i;
}

void print_queue(queue *h) {
    queue *p = h; //голова
    while (p) {
        cout << p->inf << " ";
        p = p->next;
    }
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

void find(int start, int end) {
    queue *head = NULL;
    queue *tail = NULL;
    int A[N] = {0};
    int parent[N];
    for (int i = 0; i < N; i++){
        parent[i] = -1;
    }
    A[start] = 1;
    push_queue(head, tail, start);
    bool found = false;
    while (head && !found) {
        int x = pop_queue(head, tail);
        for (int i = 0; i < N; i++) {
            if (Gr[x][i] == 1 && A[i] == 0) {
                A[i] = 1;
                parent[i] = x;
                push_queue(head, tail, i);
                if (i == end) {
                    found = true;
                    break;
                }
            }
        }
    }
    if (found){
        int path[64]; 
        int count = 0;
        int step = end;
        while (step != -1) {
            path[count++] = step;
            step = parent[step];
        }
        for (int i = count - 1; i >= 0; i--) {
            cout << path[i];
            if (i > 0) cout << " -> ";
        }
        cout << endl;
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
    cout << endl;
}

int main(){
    setlocale(LC_ALL,"RUS");
    int A, B;
    cout << "Введите A = "; cin >> A;
    cout << "Введите B = "; cin >> B;
    cout << endl;
    Graph();
    print_graph();
    cout << "Кратчайший путь из " << A << " в " << B << ": ";
    find(A, B);
    return 0;
}