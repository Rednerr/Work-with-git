#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const int N = 64;
int Gr[64][8];
int sizeGr[64] = {0};

struct queue {
    int inf;
    queue *next;
};

void push(queue *&h,queue *&t, int x){ // указатель на голову, конец, значение
    queue *r = new queue; // cоздаём новый элемент
    r->inf=x;
    r->next=NULL;
    if (!h && !t){ //если очередь пуста
        h=t=r;
    }
    else{   //если не пуста
        t->next=r; //текущий хвост указывает на новый 
        t=r;    //новый элемент хвост
    }
}

int pop(queue *&h,queue *&t){
    queue *r = h; //заполняем голову
    int i = h->inf; //сохраняем значение
    h = h->next; //двигаем голову
    if (!h){
        t = NULL; //если пусто обнуляем хвост
    }
    delete r; 
    return i;
}


void Graph() {
    int hod_x[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int hod_y[] = {1, -1, 1, -1, 2, -2, 2, -2};
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            int v = y * 8 + x;
            for (int i = 0; i < 8; i++) {
                int Ox = x + hod_x[i];
                int Oy = y + hod_y[i];
                if (Ox >= 0 && Ox < 8 && Oy >= 0 && Oy < 8) {
                    Gr[v][sizeGr[v]++] = Oy * 8 + Ox;
                }
            }
        }
    }
}

int in_numbers(const string &cell) {
    return (cell[1] - '1') * 8 + (toupper(cell[0]) - 'A');
}

string in_letters(int v) {
    string s;
    s += char('A' + (v % 8));
    s += char('1' + (v / 8));
    return s;
}

void print_queue(queue *h) {
    queue *p = h; //голова
    while (p) {
        cout << in_letters(p->inf) << " ";
        p = p->next;
    }
    cout << endl;
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
    push(head, tail, start);
    bool found = false;
    while (head && !found) {
        int x = pop(head, tail);
        for (int i = 0; i < sizeGr[x]; i++) {
            int y = Gr[x][i];
            if (A[y] == 0) {
                A[y] = 1;
                parent[y] = x;
                push(head, tail, y);
                if (y == end) {
                    found = true;
                    break;
                }
            }
        }
    }
    if (found){
        int path[64]; // Восстанавливаем путь
        int count = 0;
        int v = end;
        while (v != -1) {
            path[count++] = v;
            v = parent[v];
        }
        
        for (int i = count - 1; i >= 0; i--) {
            cout << in_letters(path[i]);
            if (i > 0) cout << " ";
        }
        cout << endl;
    } 
    else {
        cout << "Путь не найден!" << endl;
    }
}


int main() {
    setlocale(LC_ALL, "RUS");
    Graph();
    string start, end;
    cout << "Введите начальную клетку: ";
    cin >> start;
    cout << "Введите конечную клетку: ";
    cin >> end;
    find(in_numbers(start), in_numbers(end));
    return 0;
}