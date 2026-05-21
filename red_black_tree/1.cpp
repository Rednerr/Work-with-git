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
    } 
    else if (x->parent->left == x) {
        x->parent->left = y;
    } 
    else {
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
    } 
    else if (x->parent->left == x) {
        x->parent->left = y;
    } 
    else {
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


void delete_case1(tree *&tr, tree *x);
void delete_case2(tree *&tr, tree *x);
void delete_case3(tree *&tr, tree *x);
void delete_case4(tree *&tr, tree *x);
void delete_case5(tree *&tr, tree *x);
void delete_case6(tree *&tr, tree *x);

void delete_case1(tree *&tr, tree *x){
    if(!x -> parent){
        if(x -> left){
            tr = x -> left;
        }
        else{
            tr = x -> right;
        }
    }
    else{
        delete_case2(tr, x);
    }
}

void delete_case2(tree *&tr, tree *x){
    tree* B = brother(x);
    tree* P = x->parent;
    if(B && B->color == 'r'){
        P->color = 'r';
        B->color = 'b';
        if(P->left == x){
            left_rotate(tr, P);
        }
        else{
            right_rotate(tr, P);
        }
    }
    delete_case3(tr, x);
}


void delete_case3(tree *&tr, tree *x){
    tree* B = brother(x);
    if (x->parent->color == 'b' && B->color == 'b' && (!B->left || B->left->color == 'b') \
        && (!B->right || B->right->color == 'b')){
        B->color = 'r';
        delete_case1(tr, x);
    }
    else{
        delete_case4(tr, x);
    }
}

void delete_case4(tree *&tr, tree *x){
    tree* P = x->parent;
    tree* B = brother(x);
    if (x->parent->color == 'r' && B->color == 'b' && (!B->left || B->left->color == 'b') \
        && (!B->right || B->right->color == 'b')){
        B->color = 'r';
        P->color = 'b';
    }
    else{
        delete_case5(tr, x);
    }
}

void delete_case5(tree *&tr, tree *x){
    tree* P = x->parent;
    tree* B = brother(x);
    if (B->color == 'b'){
        if(P->left == x && (B->left && B->left->color == 'r') && 
            (!B->right || B->right->color == 'b')){
            B->left->color = 'b';
            B->color = 'r';
            right_rotate(tr, B);
        }
        else if(P->right == x && (B->right && B->right->color == 'r') &&
            (!B->left || B->left->color == 'b')){
            B->right->color = 'b';
            B->color = 'r';
            left_rotate(tr, B);
        }
    }
    delete_case6(tr, x);
}

void delete_case6(tree *&tr, tree *x){
    tree* B = brother(x);
    B->color = x->parent->color;
    x->parent->color = 'b';
    if (x == x->parent->left){
        if(B->right){
            B->right->color = 'b';
            left_rotate(tr, x->parent);
        }
        else{
            B->left->color = 'b';
            right_rotate(tr, x->parent);
            right_rotate(tr, x->parent);
        }
    }
}

void replace(tree *&tr, tree *x){
    tree *ch;
    if(x -> left){
        ch = x -> left;
        ch -> parent = x -> parent;
        if(x -> parent){
            if(x == x->parent->left){
                x->parent->left = ch;
            }
            else{
                x->parent->right = ch;
            }
        }
    }
    else{
        ch = x->right;
        ch->parent = x->parent;
        if(x->parent){
            if(x == x->parent->left){
                x -> parent->left = ch;
            }
            else{
                x->parent -> right = ch;
            }
        }
    }
}

tree *max_right(tree *x){
    while(x -> right){
        x = x -> right;
    }
    return x;
}

tree *max_left(tree *x){
    while(x -> left){
        x = x -> left;
    }
    return x;
}

void Delete(tree *&tr, tree *x){
    if(x->left && x->right){
        tree *buf;
        if(x->inf <= tr->inf){
            buf = max_right(x->left);
        }
        else{
            buf = max_left(x->right);
        }
        x->inf = buf->inf;
        x = buf;
    }

    if(x->left || x->right){
        tree *ch;
        if(x->left){
            ch = x->left;
        }
        else{
            ch = x->right;
        }
        replace(tr, x);
        if(x->color == 'b'){
            if(ch->color == 'r'  ){
                ch->color = 'b';
            }
            else{
                delete_case1(tr, ch);
            }
        }
        delete x;
        return;
    }
    if(x->color == 'b'){
        delete_case1(tr, x);
        if(x->parent){ 
            if(x == x->parent->left){
                x->parent->left = NULL;
            }
            else{
                x->parent->right = NULL;
            }
        }
    }
    else{
        if(x->parent){
            if(x == x->parent->left){
                x->parent->left = NULL;
            }
            else{
                x->parent->right = NULL;
            }
        }
    }
    delete x;
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

void print(tree* node) {
    if (node == nullptr) return;
    print(node->left);
    cout << node->inf << "(" << node->color << ") ";
    print(node->right);
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
    tree *tr = nullptr;
    string str;
    cout << "Введите числа через пробел: ";
    getline(cin, str);
    stringstream ss(str);
    vector<int> vec;
    int x;
    while (ss >> x) {
        vec.push_back(x);
    }
    tr = root(vec[0]);
    for (size_t i = 1; i < vec.size(); i++) {
        insert(tr, tr, vec[i]);
    }
    print(tr);
    cout << endl;
    int target;
    cout << "Введите узел: "; cin >> target;
    tree* node = search(tr, target);
    cout << "Высота: " << height(node) << endl;
    int dell;
    cout << "Введите удаляемый узел: "; cin >> dell;
    Delete(tr,search(tr, dell));
    print(tr);
    return 0;
}