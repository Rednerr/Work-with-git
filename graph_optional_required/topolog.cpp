#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

bool cycle = false;
map<int, list<pair<int, double>>> l_Adj;   
map<int, int> A;                       
vector<int> order;                         

void glubina(int x) {
    A[x] = 1;
    for (auto &p : l_Adj[x]) {
        int y = p.first;
        if (A[y] == 0) {
            glubina(y);
        } else if (A[y] == 1) {
            cycle = true;
            return;
        }
    }
    A[x] = 2;
}

void topolog(int x) {
    A[x] = 1;
    for (auto &p : l_Adj[x]) {
        int v = p.first;
        if (A[v] == 0) {
            topolog(v);
        }
    }
    order.push_back(x);
}

void buildGraph(istream &in) {
    int x, y;
    while (in >> x >> y) {
        bool duplicate = false;
        for (auto &p : l_Adj[x]) {
            if (p.first == y) {
                duplicate = true;
                break;
            }
        }
        if (!duplicate) {
            l_Adj[x].push_back({y, 1.0});
            if (l_Adj.find(y) == l_Adj.end())
                l_Adj[y];
        }
    }
}

void print() {
    for (auto &it : l_Adj) {
        cout << it.first << ": ";
        for (auto &p : it.second) {
            cout << p.first << " ";
        }
        cout << endl;
    }
}

int main() {
    ifstream in("graph.txt");
    buildGraph(in);
    print();
    cout << endl;
    for (auto &it : l_Adj) {
        A[it.first] = 0;
    }
    for (auto &it : l_Adj) {
        if (A[it.first] == 0) {
            glubina(it.first);
            if (cycle) break;
        }
    }
    if (cycle) {
        cout << "Граф граф содержит цикл" << endl;
        return 0;
    }
    A.clear();
    for (auto &it : l_Adj) {
        A[it.first] = 0;
    }
    order.clear();
    for (auto &it : l_Adj) {
        if (A[it.first] == 0) {
            topolog(it.first);
        }
    }
    reverse(order.begin(), order.end());
    for (size_t i = 0; i < order.size(); ++i) {
        if (i > 0) cout << " -> ";
        cout << order[i];
    }
    cout << endl;
    return 0;
}