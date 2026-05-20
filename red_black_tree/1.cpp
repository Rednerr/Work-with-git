#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct tree{
    int inf;
    tree* left = nullptr;
    tree* right = nullptr;
    tree* parent = nullptr;
    char color = 'r';  // по умолчанию красный
};

void left_rotate(tree*& tr, tree* x) {
    tree* y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;
    
    if (x->parent == nullptr) {
        tr = y;
    } else if (x->parent->left == x) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

void right_rotate(tree*& tr, tree* x) {
    tree* y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;
    
    if (x->parent == nullptr) {
        tr = y;
    } else if (x->parent->left == x) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    y->right = x;
    x->parent = y;
}

tree* grandfather(tree* x) {
    return (x && x->parent) ? x->parent->parent : nullptr;
}

tree* uncle(tree* x) {
    tree* g = grandfather(x);
    if (!g) return nullptr;
    return (x->parent == g->left) ? g->right : g->left;
}

void insert_fixup(tree*& tr, tree* x) {
    while (x != tr && x->parent->color == 'r') {
        tree* g = grandfather(x);
        tree* u = uncle(x);
        
        if (u && u->color == 'r') {
            // Случай 1: дядя красный
            x->parent->color = 'b';
            u->color = 'b';
            g->color = 'r';
            x = g;
        } else {
            // Случай 2: дядя чёрный
            if (x == x->parent->right && x->parent == g->left) {
                left_rotate(tr, x->parent);
                x = x->left;
            } else if (x == x->parent->left && x->parent == g->right) {
                right_rotate(tr, x->parent);
                x = x->right;
            }
            
            // Случай 3
            x->parent->color = 'b';
            g->color = 'r';
            if (x == x->parent->left) {
                right_rotate(tr, g);
            } else {
                left_rotate(tr, g);
            }
        }
    }
    tr->color = 'b';
}

void insert(tree*& tr, int x) {
    // Поиск места для вставки
    tree* parent = nullptr;
    tree* current = tr;
    
    while (current != nullptr) {
        parent = current;
        if (x < current->inf) {
            current = current->left;
        } else if (x > current->inf) {
            current = current->right;
        } else {
            return;  // дубликат, ничего не делаем
        }
    }
    
    // Создание нового узла
    tree* new_node = new tree;
    new_node->inf = x;
    new_node->parent = parent;
    new_node->left = new_node->right = nullptr;
    new_node->color = 'r';
    
    // Вставка
    if (parent == nullptr) {
        tr = new_node;
    } else if (x < parent->inf) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    
    // Балансировка
    insert_fixup(tr, new_node);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(tree* node) {
    if (node == nullptr) return -1;
    return 1 + max(height(node->left), height(node->right));
}

void inorder_print(tree* node) {
    if (node == nullptr) return;
    inorder_print(node->left);
    cout << node->inf << "(" << node->color << ") ";
    inorder_print(node->right);
}

tree* search(tree* root, int value) {
    if (root == nullptr || root->inf == value) return root;
    return (value < root->inf) ? search(root->left, value) : search(root->right, value);
}

int main() {
    setlocale(LC_ALL, "RUS");
    cout << "Вывод высоты узла" << endl;
    
    string str;
    cout << "Введите числа: ";
    getline(cin, str);
    
    vector<int> vec;
    stringstream ss(str);
    int x;
    while (ss >> x) {
        vec.push_back(x);
    }
    
    tree* root = nullptr;
    for (int val : vec) {
        insert(root, val);
    }
    
    inorder_print(root);
    cout << endl;
    
    int target;
    cout << "Введите узел: ";
    cin >> target;
    
    tree* node = search(root, target);
    if (node) {
        cout << "Высота: " << height(node) << endl;
    } else {
        cout << "Узел не найден" << endl;
    }
    
    return 0;
}