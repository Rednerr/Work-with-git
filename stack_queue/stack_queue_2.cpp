#include <iostream>
using namespace std;

struct stack {
    int inf;
    stack *next;
};

void push(stack *&h, int x) {
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}

int pop(stack *&h) {
    int i = h->inf;
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

void repl(stack *&h) {
    if (!h) return;
    int max_val = h->inf;
    int min_val = h->inf;
    stack *temp = h;
    while (temp) {
        if (temp->inf > max_val) max_val = temp->inf;
        if (temp->inf < min_val) min_val = temp->inf;
        temp = temp->next;
    }
    reverse(h);
    stack *res = NULL;     // Создаём результирующий стек
    while (h) {
        int x = pop(h);
        push(res, x);
        if (x == max_val) {
            push(res, min_val);
        }
    }
    
    // Переворачиваем результат для правильного вывода
    h = res;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int a[] = {5,2,7,4,8,3,1,8,5,3,8,5,3,8,5,3,6,1,4,6,8,1,5};
    int n = sizeof(a) / sizeof(a[0]);
    stack *head = NULL;
    // Заполняем стек (с конца, чтобы при извлечении был правильный порядок)
    for (int i = n - 1; i >= 0; i--) {
        push(head, a[i]);
    }
    cout << "Исходная: ";
    printStack(head);
    repl(head);
    cout << "Итоговая: ";
    printStack(head);
    return 0;
}
