#include <iostream>
using namespace std;

const int N = 7;
int Gr[N][N];     // список смежности
int sizeGr[N] = {0};

void Graph() {
    for (int i = 0; i < N; i++) {
        sizeGr[i] = 0;
    }
    Gr[0][1] = 1;
    Gr[0][2] = 1;
    Gr[0][4] = 1;
    Gr[0][5] = 1;
    Gr[1][0] = 1;
    Gr[1][3] = 1;
    Gr[2][0] = 1;
    Gr[2][5] = 1;
    Gr[3][1] = 1;
    Gr[4][0] = 1;
    Gr[4][6] = 1;
    Gr[5][0] = 1;
    Gr[5][2] = 1;
    Gr[5][6] = 1;
    Gr[6][4] = 1;
    Gr[6][5] = 1;
}

void add_edge(int a, int b) {
    bool smej = true;
    if (Gr[a][b] == 1){
        smej = false;
        cout << "¬ершины уже смешные" << endl << endl;
    }
    if (smej){
        Gr[a][b] = 1;  // из a можно перейти в b
        Gr[b][a] = 1;  // из b можно перейти в a
    }
}

void print_graph() {
    cout << "—писок смежности" << endl;
    for (int i = 0; i < N; i++) { 
        cout << i; // вершина
        for (int j = 0; j < N; j++) {
            if (Gr[i][j] == 1){
                cout << " -> " << j;
            }
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
    cout << "¬ведите вершины A и B, которые соединить ребром" << endl;
    cout << "A = "; cin >> A;
    cout << "B = "; cin >> B;
    add_edge(A, B);
    print_graph();
    return 0;
}