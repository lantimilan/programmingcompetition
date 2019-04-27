#include <iostream>
using namespace std;

void rorate(int a[], int n, int d) {
    int b = 0, e = n, m = d;
    while (b < m) {
        int l1 = m-b, l2 = e-m;
        int l = min(l1, l2);
        for (int i = 0; i < l; ++i) {
            swap(a[b+i], a[m+i]);
        }
        
        if (l1 < l2) e -= l;
        else b += l;
    }
}
int main() {
    int a[] = {1, 2, 3};
    int n = sizeof a / sizeof (int);
    rorate(a, n, 2);
    for (int i = 0; i < n; ++i) cout << a[i] << " ";
    cout << endl;
}
