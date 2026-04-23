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
    
    // Проверяем текущий узел
    if (tr->right && !tr->left) {
        cout << tr->inf << " ";
    }
    
    // Рекурсивно обходим левое и правое поддеревья
    printNodesWithOnlyRight(tr->left);
    printNodesWithOnlyRight(tr->right);
}

void inorder(tree *tr){ // прямой обход
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

// tree *find(tree *tr, int x){//поиск
//     if (! tr || tr->right){//нашли или дошли до конца ветки
//         return tr;
//     }
//     if (x < tr->inf){
//         return find(tr->left, x);//ищем по левой ветке
//     }
//     else{
//         return find(tr->right, x);//ищем по правой ветке
//     }
// }

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
    cout << "Узлы имеющие только правого ребёнка: ";
    printNodesWithOnlyRight(tr);
    return 0;
}