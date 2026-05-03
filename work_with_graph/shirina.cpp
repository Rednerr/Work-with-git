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


void printStack(stack *h) {
    stack *temp = NULL;
    stack *current = h;
    while (current) {
        push_stack(temp, current->inf);
        current = current->next;
    }
    while (temp) {
        cout << pop_stack(temp) << " ";
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

void shirina(int x){
    queue *head = NULL;
    queue *tail = NULL;
    int A[N] = {0};  // · создаем массив A и заполняем его нулями
    A[x] = 1; //помечаем вершину x как посещенную
    vector<int> result; // результат
    push_queue(head, tail, x);
    while (head) {
        int h = pop_queue(head, tail); //извлекаем голову очереди(ч)
        for (int i = 0; i < N; i++) {
            if (Gr[h][i] == 1 && A[i] == 0){ // существует непосещенная вершина, смежная x (A[Gr[x][i]] == 0)
                A[i] = 1; // помечаем Gr[h][i] как посещенную вершину
                result.push_back(i);
                push_queue(head, tail, i); //помещаем ее в очередь
            }
        }
    }
    bool flag = true;
    for(int i = 0; i < N; i++){
        if (A[i] == 0){
            cout << "Граф несвязный";
            flag = false;
            break;
        }
    }
    if (flag){
        cout << "Граф связный";
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
    Graph();
    print_graph();
    shirina(0);
    return 0;
}