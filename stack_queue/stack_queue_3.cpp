#include <iostream>
using namespace std;

struct queue{
    int inf;
    queue *next;
};
  
void push(queue *&h,queue *&t, int x){ // указатель на голову, конец, значение
    queue *r = new queue; // cоздаЄм новый элемент
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
    queue *r = h; //заполн€ем голову
    int i = h->inf; //сохран€ем значение
    h = h->next; //двигаем голову
    if (!h){
        t = NULL; //если пусто обнул€ем хвост
    }
    delete r; 
    return i;
}

void repl(queue *&h,queue *&t){
    int min_val = h->inf; 
    queue *temp = h; //временный указатель
    while(temp && temp->next){   // пока не дошли до конца очереди
        if (temp->inf == temp->next->inf){
            queue *clone = temp->next;
            temp->next = clone->next;
            if (!temp->next){
                t = temp;
            }
            delete clone;
        }
        else{
            temp = temp->next;
        }
    }
}

void print_queue(queue *h) {
    queue *p = h; //голова
    while (p) {
        cout << p->inf << " ";
        p = p->next;
    }
    cout << endl;
}

int main(){
    setlocale(LC_ALL,"RUS");
    int a[] = {1,1,1,3,3,3,2,2,5,5,5,6,7,8,8,9};
    int n = sizeof(a) / sizeof(a[0]);
    queue *head = NULL;
    queue *tail = NULL;
    for(int i = 0; i < n; i++){
        push(head, tail, a[i]);
    }
    cout << "»сходна€:" << endl;
    print_queue(head);
    repl(head, tail);
    cout << "»тогова€" << endl;
    print_queue(head);
    return 0;
}