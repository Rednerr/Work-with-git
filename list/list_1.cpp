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

int find(list *h, list *t){
    int max_find = INT_MIN;
    list *p = h;
    while (p){
        if(p->inf > max_find){
            max_find = p->inf;
        }
        p = p->next;
    }
    return max_find;
}

void insert_after(list *&h, list *&t, list *r, int y){
    list *p = new list;
    p->inf = y;
    if (r == t){
        p->next = NULL;
        p->prev = r;
        r->next = p;
        t = p;
    }
    else{
        r->next->prev = p;
        p->next = r->next;
        p->prev = r;
        r->next = p;
    }    
}

void repl(list *&h, list *&t){
    int last = t->inf;
    int max_find = find(h, t);
    list *p = h;   
    while(p){
        if (p->inf == last){
            insert_after(h, t, p, max_find);
            p = p->next;
        }
        p = p->next;
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
    repl(head,tail);
    print(head, tail);
    del_list(head);
    return 0;
}