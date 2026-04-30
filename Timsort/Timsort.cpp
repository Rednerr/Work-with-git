#include <iostream>
#include <vector>
using namespace std;

int RUN = 32;

void vstavka(vector<int>& a, int l, int r){
    for (int i = l + 1; i <= r; i++){
        int j = i;
        while(j > l && a[j] < a[j - 1]){
            swap(a[j], a[j-1]);
            j--;
        }
    }
}

void merge(vector<int>& a, int l, int r, int m){
    if ((l >= r) or (m < l) or (m > r)) return; 
    if ((r - l + 1 == 2) && (a[r] < a[l])){ 
        swap(a[l],a[r]);
        return;
    }
    vector<int> buf(r - l + 1);
    int cur = 0;
    int i = l;
    int j = m + 1;
    while(r - l + 1 != cur){
        if (i > m){  
            for (int k = j; k <= r; k++){ 
                buf[cur] = a[k];
                cur++;
            }
            break;
        }
        else if (j > r){ 
            for(int k = i; k <= m; k++){ 
                buf[cur] = a[k];
                cur++;
            }
        }
        else if (a[j] < a[i]){ 
            buf[cur] = a[j]; 
            cur++;
            j++;
        }
        else{   
            buf[cur] = a[i]; 
            cur++;
            i++;
        }
    }
    for(int i = 0; i < buf.size(); i++){
        a[l+i] = buf[i]; 
    }
}

void Timsort(vector<int>& a, int& n){
    if (n <= 1) return;
    for(int i = 0; i < n; i += RUN){
        int right = min(i + RUN - 1, n -1);
        vstavka(a, i, right);
    }
    for (int size = RUN; size < n; size = size * 2){
        for(int left = 0; left < n; left += size * 2){
            int mid = min(left + size - 1, n - 1);
            int right = min(left + size * 2 - 1, n - 1);
            if(mid < right){
                merge(a, left, right, mid);
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    vector<int> a = {93, 34, 17, 5, 81, 9, 77, 24, 7, 56, 8, 85, 73, 70, 42, 71, 63, 41, 28, 46, 38, 99, 6, 38, 72};
    int n = a.size();
    cout << "Набор чисел ";
    for (int x : a) cout << x << " ";
    cout << endl;
    Timsort(a, n);
    cout << "Набор после сортировки: " ;
    for (int x : a) cout << x << " ";
    cout << endl;
    return 0;
}
