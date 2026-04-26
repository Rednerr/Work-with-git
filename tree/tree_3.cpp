#include <iostream>
using namespace std;

struct tree{
    int inf;
    tree *left;
    tree *right;
    tree *parent;
};

tree *node(int x){
    tree *n = new tree;
    n->inf = x;
    n->parent = NULL;
    n->right = NULL;
    n->left = NULL;
    return  n;
}

void printNodesWithOnlyRight(tree *tr) {
    if (!tr) return;
    
    // ????????? ??????? ????
    if (tr->right && !tr->left) {
        cout << tr->inf << " ";
    }
    
    // ?????????? ??????? ????? ? ?????? ??????????
    printNodesWithOnlyRight(tr->left);
    printNodesWithOnlyRight(tr->right);
}

void inorder(tree *tr){ // ?????? ?????
    if(tr){
        inorder(tr->left);
        cout << tr->inf << " ";
        inorder(tr->right);
    }
}

void insert(tree *&tr, int x){
    tree *n = node(x);
    if (!tr) {
        tr = n;
    }
    else{
        tree *y = tr;
        while(y){
            if(n->inf > y->inf){
                if (y->right){
                    y = y->right;
                }
                else{
                    n->parent = y;
                    y->right = n;
                    break;
                }
            }
            else if(n->inf < y->inf){
                if (y->left){
                    y = y->left;
                }
                else{
                    n->parent = y;
                    y->left = n;
                    break;
                }
            }
        }
    }
}

tree *find(tree *tr, int x){//поиск
    if (!tr || tr->right){//нашли или дошли до конца ветки
        return tr; //узел 
    }
    if (x < tr->inf){
        return find(tr->left, x); //ищем по левой ветке
    }
    else{
        return find(tr->right, x); //ищем по правой ветке
    }
}

tree *Min(tree *tr){
    if (!tr->left) return tr; //нет левого ребёнка вовращает узел
    else return Min(tr->left); // идём дальше по левой ветке
}

tree *Next(tree*tr, int x){//поиск следующего для Delete
    tree* n = find(tr, x);
    if (n->right){//если есть левый ребёнок
        return Min(n->right); //ищем минимальный по правой ветке
    }
    tree *y = n->parent; //родитель
    while(y && n == y->right){ //пока не дошли до корня и узел - правый ребёнок
        n = y; // идём вверх по дереву
        y = y->parent;
    }
    return y;
}

void Delete(tree *&tr, tree *v){ // удаляем узел v
    tree *p = v->parent; // указ на родителя
    if (!p) tr = NULL; //дерево содержит один узел, то дерево пустое  
    else if (!v->left && !v->right){ // если нет детей
        if (p->left == v){ //если v левый ребёнок p, меняем на NULL
            p->left = NULL;
        }
        if (p->right == v){//если v правый ребёнок p, меняем на NULL
            p->right = NULL;
        }
        delete v; 
    }
    else if(!v->left || !v->right){ // если один ребёнок у v
        if (!p){ //начинается с v
            if (!v->left){ // если нет левого ребёнка
                tr = v->right;// правый теперь корень
                v->parent = NULL;
            }
            else{//если нет правого
                tr = v->left;
                v->parent = NULL;
            }
        }
        else{ //v не корень 
            if (!v->left){ // есть првый ребёнок
                if (p->left == v){//если узел v левый ребёнок
                    p->left = v->right; // правый ребёнок v становится левым ребёнком деда
                }
                else{ //если узел v правый ребёнок
                    p->right = v->right;
                }
            }
            else{ // есть левый ребёнок у v 
                if(p->left == v){ //узел v левый ребёнок деда
                    p->left = v->left; // левый ребенок теперь левый ребёнок деда
                }
                else{ //узел v правый ребёнок деда
                    p->right = v->left; // левый ребенок теперь правый ребёнок деда
                }
            }
            delete v;
        }
    }
    else{ // есть два ребёнка
        tree *succ = Next(tr, v->inf); //узел следующий за удаляемым
        v->inf = succ->inf; //присваиваем значение удаляемому узлу
        if(succ->parent->left == succ){ // если succ левый ребёнок
            succ->parent->left = succ->right; // его правый ребёнок становится левым ребёнком своего деда
            if(succ->right){ // если этот ребёнок существует
                succ->right->parent = succ->parent; // его родителем становится дед 
            }
        }
        else{ // succ правый ребёнок
            succ->parent->right = succ->right; // его правый ребёнок становится правым ребёнком своего деда
            if (succ->right){ // если этот ребёнок существует
                succ->right->parent = succ->parent;
            }
        }
        delete succ;
    }
}

void postorder_chet(tree *tr){ //обратный обход и удаление
    if(tr){
        postorder_chet(tr->left);
        postorder_chet(tr->right);
        if (tr->inf % 2 == 0){
            tree* v = find(tr, tr->inf);
            Delete(tr, v);
        }
    }
}

int main(){
    setlocale(LC_ALL,"RUS");
    int x, n;
    cout << "Введите количество чисел: "; cin >> n;
    tree *tr = NULL;
    for(int i = 0; i < n; i++){
        cout << i << ": ";
        cin >> x;
        insert(tr, x);
    }
    cout<< "Прямой обход: ";
    inorder(tr);
    cout << endl;
    postorder_chet(tr);
    cout<< "Прямой обход: ";
    inorder(tr);
    return 0;
}