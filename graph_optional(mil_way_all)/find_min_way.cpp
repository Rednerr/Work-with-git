#include <iostream>
#include <vector>
using namespace std;

const int N = 7;
int Gr[N][N];     //матрица смежности
int sizeGr[N] = {0};

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
        int h = pop_queue(head, tail);
        for (int i = 0; i < sizeGr[h]; i++) {
            int y = Gr[h][i];
            if (A[y] == 0) {
                A[y] = 1;
                parent[y] = h;
                push_queue(head, tail, y);
                if (y == end) {
                    found = true;
                    break;
                }
            }
        }
    }
    if (found){
        int path[N]; 
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
        cout << i << " -> "; //вершина
        for (int j = 0; j < sizeGr[i]; j++) {
            cout << Gr[i][j]; //её смежные
            if (j < sizeGr[i] - 1) cout << " -> ";
        }
        cout << endl;
    }
    cout << endl;
}

int main(){
    setlocale(LC_ALL,"RUS");
    Graph();
    print_graph();
    int A;
    cout << "Введите начальную точку = "; cin >> A;
    cout << endl;
    for(int i = 0; i < N; i++){
        if (A != i){
            cout << A << " -> " << i << ": ";
            find(A,i);
        }
    }
    return 0;
}