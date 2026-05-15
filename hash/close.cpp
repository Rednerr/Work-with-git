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

vector<people> inFile(){
    vector<people> x;
    people temp;
    string line;
    while(getline(in, line)){ // читаем построчно
        if(line.empty()) continue;
        vector<string> parts; //вектор для данных об одном человеке
        string tmp; 
        for(int i = 0; i < line.length(); i++) {
            if(line[i] == ',') {
                parts.push_back(tmp);
                tmp.clear();  // очищаем для следующей части
                i++;
            } 
            else {
                tmp += line[i];
            }
        }
        if (!tmp.empty()) {
            parts.push_back(tmp); //добавляем последние данные, если дошли до конца 
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

struct HashTable{
    people data;
    bool close = false;
};

int hashFunction1(int salary, int M) {                         // исправлено: проверка пустой строки
    return 1 + (salary % (M-1));
}

int hashFunction2(const string& experience, int M) {                         // исправлено: проверка пустой строки
    return (experience[0]+experience[1]) % M;
}

int hashFunction(const string& experience, int salary,int i, int M) {                         // исправлено: проверка пустой строки
    return (hashFunction1(salary, M) + i * hashFunction2(experience, M)) % M;
}

vector<HashTable> buildHash(vector<people> &A, int M){
    vector<HashTable> table(M);
    for (int i = 0; i < A.size(); i++){
        int j = 0;
        while (j < M){
            int k = hashFunction(A[i].experience, A[i].salary, j, M);
            if (!table[k].close){
                table[k].data = A[i];
                table[k].close = true;
                break;
            }
            j++;
        }
    }
    return table;
}

void printHash(vector<HashTable> &table){
    for (int i = 0; i < table.size(); i++){
        cout << "[" << i << "] ";
        if (!table[i].close){
            cout << "NULL" << endl;
        }
        else{
            print(table[i].data);
        }
    }
}

void findElement(vector<HashTable> &table, const string& experience, int salary, int M){
    cout << "Finding salary " << experience << ", year " << salary << endl;
    int i = 0;
    bool found = false;
    while (i < M){
        int k = hashFunction(experience, salary, i, M);
        if (!table[k].close){
            break;
        }
        if (table[k].data.experience == experience && table[k].data.salary == salary){
            print(table[k].data);
            found = true;
            break;
        }
        i++;
    }
    if (!found){
        cout << "Unable to find records" << endl;
    }
}

int main() {
    vector<people> x = inFile();
    int M = 37;
    vector<HashTable> table = buildHash(x, M);
    
    printHash(table);
    
    string exp_find;
    int salary_find;
    cout << "find experience and salary" << endl;
    cout << "experience: ";
    getline(cin, exp_find);
    cout << "salary: ";
    cin >> salary_find;
    findElement(table, exp_find, salary_find, M);
    return 0;
}