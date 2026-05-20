#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct tree{
    int inf;
    tree* left, * right;
    tree* parent;
    char color;
};

void left_rotate(tree*& tr, tree* x) {
    tree* y = x->right;
    x->right = y->left;
    if (y->left) {
        y->left->parent = x;
    }
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
    if (y->parent == nullptr) {
        y->color = 'b';
    }
}

void right_rotate(tree*& tr, tree* x) {
    tree* y = x->left;
    x->left = y->right;
    if (y->right) {
        y->right->parent = x;
    }
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
    if (y->parent == nullptr) {
        y->color = 'b';
    }
}

tree* root(int x){
    tree*n = new tree;
    n->inf = x;
    n->left = n->right = nullptr;
    n->parent = nullptr;
    n->color = 'b';
    return n;
}

tree* node(tree* prev, int x){
    tree* n = new tree;
    n->inf = x;
    n->left = n->right = nullptr;
    n->parent = prev;
    n->color = 'r';
    return n;
}

tree* grandfather(tree* x){
    if (x && x->parent){
        return x->parent->parent;
    }
    else{
        return nullptr;
    }
} 

tree* uncle(tree *x){
    tree* g = grandfather(x);
    if (!g){
        return nullptr;
    }
    if(x->parent == g->left){
        return g->right;
    }
    else{
        return g->left;
    }
}

tree* brother(tree* x){
    if (x && x->parent){
        if (x == x->parent->left){
            return x->parent->right;
        }
        else{
            return x->parent->left;
        }
    }
    else{
        return nullptr;
    }
}

void insert_case_1(tree*& tr, tree* x);
void insert_case_2(tree*& tr, tree* x);
void insert_case_3(tree*& tr, tree* x);
void insert_case_4(tree*& tr, tree* x);
void insert_case_5(tree*& tr, tree* x);

void insert_case_1(tree*& tr, tree* x){
    if (!x->parent){
        x->color = 'b';
    }
    else{
        insert_case_2(tr, x);
    }
}

void insert_case_2(tree*& tr, tree* x){
    if (x->parent->color == 'r'){
        insert_case_3(tr,x);
    }
}

void insert_case_3(tree*& tr, tree* x){
    tree* g = grandfather(x);
    tree* u = uncle(x);
    if (u && u->color == 'r' && x->parent->color == 'r'){
        x->parent->color = 'b';
        u->color = 'b';
        g->color = 'r';
        insert_case_1(tr,g);
    }
    else{
        insert_case_4(tr,x);
    }
}

void insert_case_4(tree*& tr, tree* x){
    tree* g = grandfather(x);
    tree* p = x->parent;
    if (p->right == x && g->left == p){
        left_rotate(tr, p);
        x = x->left;
    }
    else if(p->left == x && g->right == p){
        right_rotate(tr, p);
        x = x->right;
    }
    insert_case_5(tr, x);
}

void insert_case_5(tree*& tr, tree* x){
    tree* g = grandfather(x);
    tree* p = x->parent;
    p->color = 'b';
    g->color = 'r';
    if (x == p->right && p == g->right){
        left_rotate(tr, g);
    }
    else{
        right_rotate(tr, g);
    }
}

void insert(tree*& tr, tree* prev, int x) {
    if(!tr){
        tree* n = root(x);
        tr = n;
    }
    else{
        if (x < prev->inf && !prev->left){
            prev->left = node(prev, x);
            insert_case_1(tr, prev->left);
        }
        else if(x < prev->inf && prev->left){
            insert(tr, prev->left, x);
        }
        else if(x > prev->inf && !prev->right){
            prev->right = node(prev, x);
            insert_case_1(tr, prev->right);
        }
        else if(x > prev->inf && prev->right){
            insert(tr, prev->right, x);
        }
    }
}

int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int height(tree* node) {
    if (node == nullptr) {
        return -1;
    }
    int left = height(node->left);
    int right = height(node->right);
    return 1 + max(left, right);
}

void inorder_print(tree* node) {
    if (node == nullptr) return;
    inorder_print(node->left);
    cout << node->inf << "(" << node->color << ") ";
    inorder_print(node->right);
}

tree* search(tree* tr, int x) {
    if (tr == nullptr || tr->inf == x) {
        return tr;
    }
    else if (x < tr->inf) {
        return search(tr->left, x);
    } 
    else{
        return search(tr->right, x);
    }
}

int main(){
    setlocale(LC_ALL,"RUS");
    cout << "Вывод высоты узла" << endl;
    vector<int> vec;
    string str;
    cout << "Введите числа: ";
    getline(cin, str);
    int x;
    stringstream ss(str);
    while (ss >> x){
        vec.push_back(x);
    }
    tree* tr = nullptr;
    for(int i : vec){
        insert(tr, nullptr, i);
    }
    inorder_print(tr);
    cout << endl;
    int target;
    cout << "Введите узел: "; cin >> target;
    tree* node = search(tr, target);
    cout << "Высота: " << height(node);
    return 0;
}