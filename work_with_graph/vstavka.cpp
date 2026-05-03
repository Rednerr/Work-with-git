#include <iostream>
#include <vector>
using namespace std;

const int N = 7;
int Gr[N][N];     // список смежности
int sizeGr[N] = {0};

void Graph() {
    for (int i = 0; i < N; i++) {
        sizeGr[i] = 0;
    }
    Gr[0][sizeGr[0]++] = 1;
    Gr[0][sizeGr[0]++] = 2;
    Gr[0][sizeGr[0]++] = 4;
    Gr[0][sizeGr[0]++] = 5;
    Gr[1][sizeGr[1]++] = 0;
    Gr[1][sizeGr[1]++] = 3;
    Gr[2][sizeGr[2]++] = 0;
    Gr[2][sizeGr[2]++] = 5;
    Gr[3][sizeGr[3]++] = 1;
    Gr[4][sizeGr[4]++] = 0;
    Gr[4][sizeGr[4]++] = 6;
    Gr[5][sizeGr[5]++] = 0;
    Gr[5][sizeGr[5]++] = 2;
    Gr[5][sizeGr[5]++] = 6;
    Gr[6][sizeGr[6]++] = 4;
    Gr[6][sizeGr[6]++] = 5;
}

void add_edge(int a, int b) {
    bool smej = true;
    for(int i; i < N;i++){
        if (Gr[a][i] == b){
            smej = false;
            cout << "Вершины уже смешные" << endl << endl;
            break;
        }
    }
    if (smej){
        Gr[a][sizeGr[a]++] = b;  // из a можно перейти в b
        Gr[b][sizeGr[b]++] = a;  // из b можно перейти в a
    }
}

void print_graph() {
    cout << "Список смежности" << endl;
    for (int i = 0; i < N; i++) { 
        cout << i << " -> "; // вершина
        for (int j = 0; j < sizeGr[i]; j++) {
            cout << Gr[i][j]; // её смежные
            if (j < sizeGr[i] - 1) cout << " -> ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    Graph();
    print_graph();
    int A, B;
    cout << "Введите вершины A и B, которые соединить ребром" << endl;
    cout << "A = "; cin >> A;
    cout << "B = "; cin >> B;
    add_edge(A, B);
    print_graph();
    return 0;
}