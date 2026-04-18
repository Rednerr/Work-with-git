#include <iostream>
using namespace std;
#include <iomanip>
#include <vector>

const int N = 7;
int Gr[N][N];     // список смежности
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

int print_queue(queue *h) {
    int count_queue = 0; // счётчик элементов очереди для setw()
    queue *p = h; //голова
    while (p) {
        cout << p->inf << " ";
        p = p->next;
        count_queue+= 2;
    }
    if (h == NULL){ // если элементов нет 
        cout << setw(8) << "empty";
        count_queue = 5;
    }
    return count_queue; //счётчик для setw()
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

void shirina(int x){
    queue *head = NULL;
    queue *tail = NULL;
    int A[N] = {0};  // · создаем массив A и заполняем его нулями
    A[x] = 1; //помечаем вершину x как посещенную
    vector<int> result; // результат
    push_queue(head, tail, x);
    result.push_back(x);
    while (head) {
        int count_Grx = 0;
        int h = pop_queue(head, tail); //извлекаем голову очереди(ч)
        for (int i = 0; i < sizeGr[h]; i++) {
            if (A[Gr[h][i]] == 0) { // существует непосещенная вершина, смежная x (A[Gr[x][i]] == 0)
                A[Gr[h][i]] = 1; // помечаем Gr[h][i] как посещенную вершину
                push_queue(head, tail, Gr[h][i]); //помещаем ее в очередь
                result.push_back(Gr[h][i]);
            }
        }
        cout << setw(6) <<  h << setw(15); //текущ вершина
        for (int j = 0; j < sizeGr[h]; j++) {
            cout << Gr[h][j] << " "; //Gr[x]
            count_Grx+=2;
        }
        cout << setw(13 - count_Grx);
        for (int i = 0; i < N; i++) {
            cout << A[i] << " ";    //массив А
        }
        cout << setw(4);
        cout << setw(15 - print_queue(head)); //очередь
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << " "; //результат
        }
        cout << endl;  
    }
    for (int i = 0; i < N; i++) {
        if (A[i] == 0) {
            shirina(i);//вызываем для непосещённой вершины
        }
    }
}


void print_graph() {
    cout << "Список смежности" << endl;
    for (int i = 0; i < N; i++) {
        cout << i << " -> ";
        for (int j = 0; j < sizeGr[i]; j++) {
            cout << Gr[i][j];
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
    cout << "Обход в ширину" << endl;
    cout  << setw(10) << "Текущая вершина" << setw(10) << "Gr[x]" << setw(15) << "Массив A" << setw(15) << "Очередь" << setw(15)  << "Результат" << endl;
    shirina(0);
    cout << endl;
    return 0;
}