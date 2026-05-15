#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
ifstream in("hash.txt");

struct date {
    int dd, mm, yy;
};

date Str_to_date(string str) {
    date x;
    string temp = str.substr(0, 2);
    x.dd = atoi(temp.c_str());
    temp = str.substr(3, 2);
    x.mm = atoi(temp.c_str());
    temp = str.substr(6, 4);
    x.yy = atoi(temp.c_str());
    return x;
}

struct people {
    string surname;
    string post;
    date birth;
    string experience;
    int salary;
};

struct list {
    people data;
    list *next;
    list *prev;
};

void push(list *&h, list *&t, people x) {
    list *r = new list;
    r->data = x;      
    r->next = NULL;
    if (!h && !t) {
        r->prev = NULL;
        h = r;
    }
    else {
        t->next = r;
        r->prev = t;
    }
    t = r;
}

void del_node (list *&h, list *&t, list *r){
    if (r == h && r == t){
        h = t = NULL;
    }
    else if (r == h){
        h = h -> next;
        h -> prev = NULL;
    }
    else if (r == t){
        t = t -> prev;
        t -> next  = NULL;
    }
    else{
        r -> next -> prev = r -> prev;
        r -> prev -> next = r -> next;
    }
    delete r;
}

void del_list(list* &h, list* &t){
    while (h){
        list *p = h;
        h = h ->  next;
        h -> prev = NULL;
        delete p;
    }
}

void print(people &x){
    cout << left << x.surname << setw(15 - x.surname.length()) << " ";
    cout << left << x.post << setw(30 - x.post.length()) << " ";
    if (x.birth.dd < 10) cout << left << '0' << x.birth.dd << '.';
    else cout << left << x.birth.dd << '.';
    if (x.birth.mm < 10) cout << left << '0' << x.birth.mm << '.';
    else cout << left << x.birth.mm << '.';
    cout << setw(6) << x.birth.yy;
    cout << left << setw(12) << x.experience;
    cout << left << setw(10) << x.salary << endl;
}

vector<people> inFile(){
    vector<people> x;
    people temp;
    string line;
    while(getline(in, line)){ 
        if(line.empty()) continue; //если строка пустая проспускаем
        vector<string> parts; 
        string tmp; 
        for(int i = 0; i < line.length(); i++) {
            if(line[i] == ',') {
                parts.push_back(tmp);
                tmp.clear();  
                i++;
            } 
            else {
                tmp += line[i];
            }
        }
        if (!tmp.empty()) {
            parts.push_back(tmp);  
        }         
        temp.surname = parts[0];
        temp.post = parts[1];
        temp.birth = Str_to_date(parts[2]);
        temp.experience = parts[3];
        temp.salary = atoi(parts[4].c_str());
        x.push_back(temp);
    }
    return x;
}

struct HashTable {
    list* head; 
    list* tail;      
};

int hashFunction(const string& experience, int M) { //деление по стажу
    return (experience[0]+experience[1]) % M;
}

vector<HashTable> buildHash(vector<people> &A, int M){
    vector<HashTable> table(M); //вектор из M таблиц
    for (int i = 0; i < A.size(); i++){
        int k = hashFunction(A[i].experience, M); //индекс корзины по стажу
        push(table[k].head, table[k].tail, A[i]); //добавляем в эту корзину
    }
    return table;
}

void printHash(vector<HashTable> &table){
    for (int i = 0; i < table.size(); i++){
        cout << "[" <<  i << "]";
        if (!table[i].head){
            cout << "NULL" << endl;
        } 
        else{
            cout << endl;
            list* p = table[i].head;
            while (p){
                print(p -> data);
                p = p -> next;
            }
        }
    }
}

void find(vector<HashTable> &table, int M, const string& experience) {
    int k = hashFunction(experience, M); //индекс корзины по стажу
    list* p = table[k].head;
    bool found = true;
    while (p) {
        if (p->data.experience == experience) {
            print(p -> data);
            found = false;
        }
        p = p->next;
    }
    if (found){
        cout <<"Not found " << experience << endl;
    }
}

void del(vector<HashTable> &table, int M, const string& experience) {
    int k = hashFunction(experience, M);//индекс корзины по стажу
    list* p = table[k].head;
    while (p) {
        list* next = p -> next;
        if (p->data.experience == experience) {
            del_node(table[k].head, table[k].tail, p);
        }
        p = p->next;
    }
}

int main() {
    vector<people> x = inFile();
    int M = 31;
    vector<HashTable> table = buildHash(x, M);
    
    printHash(table);
    
    string exp_find;
    cout << "find experience: ";
    getline(cin, exp_find);
    find(table, M, exp_find);
    cout << endl;
    string exp_del;
    cout << "delete experience: "; 
    getline(cin, exp_del);
    del(table, M, exp_del);
    cout << endl;
    cout << "Table after delete:" << endl;
    cout << endl;
    printHash(table);
    for (int i = 0; i < table.size(); i++){
        del_list(table[i].head, table[i].tail);
    }
    return 0;
}