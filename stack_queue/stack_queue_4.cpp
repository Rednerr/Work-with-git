#include <iostream>
using namespace std;

struct stack {
    char inf;
    stack *next;
};

void push(stack *&h, char x) {
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

char pop(stack *&h) {
    char i = h->inf;
    stack *r = h;
    h = h->next;
    delete r;
    return i;
}

void reverse(stack *&h) {
    stack *head1 = NULL;
    while (h) {
        push(head1, pop(h));
    }
    h = head1;
}

void printStack(stack *h) {
    stack *temp = NULL;
    stack *current = h;
    while (current) {
        push(temp, current->inf);
        current = current->next;
    }
    while (temp) {
        cout << pop(temp) << " ";
    }
    cout << endl;
}

void repl(stack *&stak) {
    if (!stak) return;
    char sogl[] = {'q','w', 'r', 't', 'p', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm'};
    bool soglas = true;
    stack *res = NULL;
    int n1 = sizeof(sogl) / sizeof(sogl[0]);
    reverse(stak);
    while(stak){
        char x = pop(stak);
        push(res, x);
        if (soglas){
            for(int i = 0; i < n1; i++){
                if (x == sogl[i]){
                    soglas = false;
                    push(res, '!');
                    break;
                }   
            }
        }    
    }
    stak = res; 
}

int main() {
    setlocale(LC_ALL, "RUS");
    char a[] = {'q', 'w', 'e', 'r', 't', 'u', 'i', 'o', 'p', 's', 'd', 'a'};
    int n = sizeof(a) / sizeof(a[0]);
    stack *head = NULL;
    // Заполняем стек (с конца, чтобы при извлечении был правильный порядок)
    for (int i = 0; i < n; i++) {
        push(head, a[i]);
    }
    cout << "Исходная: ";
    printStack(head);
    repl(head);
    cout << "Итоговая: ";
    printStack(head);
    return 0;
}
