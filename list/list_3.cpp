#include <iostream>
using namespace std;

struct list{
    int inf;
    list *next;
    list *prev;
};

void push(list *&h, list *&t, int x){
    list *r = new list;
    r->inf = x;
    r->next = NULL;
    if (!h && !t){
        r->prev = NULL;
        h = r;
    }
    else {
        t->next = r;
        r->prev = t;
    }
    t = r;
}

void print(list *h, list *t){
    list *p = h;
    while (p){
        cout << p->inf << " ";
        p = p->next;
    }
    cout << endl;
}

void swap(list *&head, list *&tail, list *a, list *b){// a и b - соседние узлы
    list *prev_a = a->prev; // узел перед a
    list *next_b = b->next;   // после b
    if (prev_a) {
        prev_a->next = b; //если перед а есть узел, то он указывает на b
    } 
    else {
        head = b;  // a был головой, теперь голова - b
    }
    b->prev = prev_a; //b указывает на 
    b->next = a; //меняем местами a и b
    a->prev = b;
    a->next = next_b; //a связывается с next_b
    if (next_b) {
        next_b->prev = a;
    } 
    else {
        tail = a;  // b был хвостом, теперь хвост - a
    }
}

void sort(list *&h, list *&t, int n){
    for (int i = 0; i < n - 1; i++) { //внешний цикл 
        list *p = h;
        for (int j = 0; j < n - i - 1; j++) {   // Проходим по списку до (N-i-1)-го элемента
            list *next_p = p->next;
            if (p->inf > next_p->inf) {
                swap(h, t, p, next_p);
            }
            else {
                p = p->next;
            }
        }
    }
}

void del_list(list *&h){
    while (h) {
        list *p = h;
        h = h->next;
        delete p;
    }
}

int main(){
    setlocale(LC_ALL, "RUS");
    int a[] = {8, 2, 1, 6, 8, 8, 1, 2, 2, 8, 2};
    int n = sizeof(a) / sizeof(a[0]);
    list *head = NULL;
    list *tail = NULL;
    for (int i = 0; i < n; i++) {
        push(head, tail, a[i]);
    }
    print(head, tail);
    sort(head,tail, n);
    print(head, tail);
    del_list(head);
    return 0;
}