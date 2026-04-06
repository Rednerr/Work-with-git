#include <iostream>
using namespace std;

struct queue{
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

void repl(queue *&h,queue *&t){
    queue *temp_h = NULL;
    queue *temp_t = NULL;
    int x = pop(h,t);
    push(temp_h,temp_t, x);
    while(h){
        int y = pop(h,t);
        if (x != y){
            push(temp_h,temp_t, y);
            x = y;
        }
    } 
    h = temp_h; //обновляем указать не новую голову
    t = temp_t; //обновляем указатель на новый хвост
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
    cout << "Исходная:" << endl;
    print_queue(head);
    repl(head, tail);
    cout << "Итоговая" << endl;
    print_queue(head);
    return 0;
}