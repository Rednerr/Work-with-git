#include <iostream>
#include <cmath>
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

bool prostoe(int n){
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    int limit = sqrt(n);
    for (int i = 3; i <= limit; i += 2){
        if (n % i == 0) return false;
    }
    return true;
}

list *find(list *h, list *t){
    list *p = h;
    while (p){
        if(prostoe(p->inf)){
            return p;
        }
        p = p->next;
    }
    cout << "Простых чисел нет" << endl;
    print(h,t);
    return 0;
}

void repl(list *&h, list *&t, list *prostoe){ //с
    list *p = prostoe->prev; //узел, который был перед cписком простых
    t->next = h; //хвост на голову
    h->prev = t; //голова на хвост
    h = prostoe; // новая голова начало списка простого
    t = p; // новй хвост узел p 
    t->next = NULL; // хвост не указывает вперёд и также голова назад
    h->prev = NULL;
    list *last = t; // удаляем последний 
    t = last->prev;
    t->next = NULL;
    delete last;
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
    int a[] = {4, 8, 6, 9, 1, 2, 3, 4, 5, 7};
    int n = sizeof(a) / sizeof(a[0]);
    list *head = NULL;
    list *tail = NULL;  
    for (int i = 0; i < n; i++) {
        push(head, tail, a[i]);
    }
    print(head, tail);
    list *find_prostoe = find(head, tail);
    repl(head,tail, find_prostoe);
    print(head, tail);
    del_list(head);
    return 0;
}