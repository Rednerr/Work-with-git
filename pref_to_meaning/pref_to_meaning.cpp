#include <iostream>
#include <string>
#include <cctype>
using namespace std;

struct stack {
    string inf;
    stack *next;
};

void push(stack *&h, string x) {
    stack *r = new stack;
    r->inf = x;
    r->next = h;
    h = r;
}


string pop(stack *&h) {
    string i = h->inf;
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

double znak(double a, double b, const string& op){
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") return a / b;
    return 0;
}

void pref_to_meaning(const string& str){
    stack *head = NULL;
    int i = 0;
    while (i < str.length()){
        if (str[i] ==  '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'){
            string sign;
            sign = str[i];
            push(head, sign);
            i++;
        }
        else{
            string sign2;
            sign2 = str[i];
            string b = sign2;
            i++;
            if (head != NULL && (head->inf == "+" || head->inf == "-" || head->inf == "*" || head->inf == "/")){
                push(head, b); 
            }
            else{
                string bz = b;
                while(head != NULL && head->inf != "+" && head->inf != "-" && head->inf != "*" && head->inf != "/"){
                    string a = pop(head); 
                    string op = pop(head);
                    double result = znak(stod(a), stod(bz), op);
                    bz = to_string(result);
                }
                push(head, bz);
            }
        }
    }
    if (head != NULL) {
        cout << "Результат: " << head->inf << endl;
    }
}

int main(){
    setlocale(LC_ALL, "RUS");
    string str = "+5*++3/++2*4-312414";
    pref_to_meaning(str);
    return 0;
}

