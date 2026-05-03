#include <iostream>
using namespace std;

const int N = 7;
int Gr[N][N];     // матрица смежности
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

void print_graph() {
    cout << "Список смежности" << endl;
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
    int x;
    cout << "Введите вершину: ";
    cin >> x;
    int count = 0;
    for(int i = 0; i < N; i++){
        if (Gr[x][i] == 1){
            count++;
        }
    }
    cout << "Количество смежных вершин: " << count << endl;
    return 0;
}