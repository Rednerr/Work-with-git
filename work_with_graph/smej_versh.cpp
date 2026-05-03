#include <iostream>
#include <vector>
using namespace std;

const int N = 7;
int Gr[N][N];     // матрица смежности
int sizeGr[N] = {0};

void Graph() {
    for (int i = 0; i < N; i++) {
        sizeGr[i] = 0;
    }
    Gr[0][sizeGr[0]++] = 1; // для 0
    Gr[0][sizeGr[0]++] = 2;
    Gr[0][sizeGr[0]++] = 4;
    Gr[0][sizeGr[0]++] = 5;
    Gr[1][sizeGr[1]++] = 0; // для 1
    Gr[1][sizeGr[1]++] = 3;
    Gr[2][sizeGr[2]++] = 0; // для 2
    Gr[2][sizeGr[2]++] = 5;
    Gr[3][sizeGr[3]++] = 1; // для 3
    Gr[4][sizeGr[4]++] = 0; // для 4
    Gr[4][sizeGr[4]++] = 6;
    Gr[5][sizeGr[5]++] = 0; // для 5
    Gr[5][sizeGr[5]++] = 2;
    Gr[5][sizeGr[5]++] = 6;
    Gr[6][sizeGr[6]++] = 4; // для 6
    Gr[6][sizeGr[6]++] = 5;
}

void print_graph() {
    cout << "Список смежности" << endl;
    for (int i = 0; i < N; i++) { 
        cout << i << " -> "; // вершина
        if (sizeGr[i] == 0) {
            cout << "?";
        }
        for (int j = 0; j < sizeGr[i]; j++) {
            cout << Gr[i][j]; // её смежные
            if (j < sizeGr[i] - 1) cout << " -> ";
        }
        cout << endl;
    }
    cout << endl;
}

// Функция для вывода смежных вершин для заданной вершины
void print_adjacent_vertices(int x) {
    cout << "Вершина " << x << " смежна с: ";
    if (sizeGr[x] == 0) {
        cout << "нет смежных вершин (?)";
    } else {
        for (int j = 0; j < sizeGr[x]; j++) {
            cout << Gr[x][j];
            if (j < sizeGr[x] - 1) cout << ", ";
        }
    }
    cout << endl;
    
    // Подсчет количества смежных вершин
    cout << "Количество смежных вершин: " << sizeGr[x] << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    Graph();
    print_graph();
    int x;
    cout << "Введите вершину: ";
    cin >> x;
    print_adjacent_vertices(x);
    return 0;
}