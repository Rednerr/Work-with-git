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
    while(temp){   // пока не дошли до конца очереди
        if (temp->inf < min_val)
            min_val = temp->inf;
        temp = temp->next; //берЄм следующий элемент
    }
    int last_odd;
    bool odd = true;
    temp = h;//временный указатель на голову
    while(temp){
        if (temp->inf %2 != 0){
            last_odd = temp->inf;
            odd = false;
        }
        temp = temp->next;
    }
    if (odd){
        cout << "ЌечЄтных нет" << endl;
        return;
    }
    queue *res_h = NULL; // голова новой очереди
    queue *res_t = NULL; // хвост
    while (h){
        int x = pop(h, t); //извлекаем элемент из исходной
        push(res_h, res_t, x); // добавл€ем в новую
        if (x == min_val){
            push(res_h,res_t,last_odd);
        }
    }
    h = res_h; //обновл€ем указать не новую голову
    t = res_t; //обновл€ем указатель на новый хвост
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
    int a[] = {5,2,7,4,8,3,1,8,5,3,8,5,3,8,5,3,6,1,4,6,8,1,5};
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