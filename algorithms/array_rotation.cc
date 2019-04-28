#include <iostream>
using namespace std;

// Algorithm:
// Let A and B be the two partitions
// if A is shorter, then split B into Bl and Br, and swap(A, Br), then recurse
// on BrBl
// else B is shorter, then split A into Al and Ar, and swap(Al, B), then
// recurse on ArAl
// Other O(n) rotation algorithms:
// 1. Let g = gcd(n, d)
// then rotate a[i], a[i+g], a[i+2g], ..., for i = 0 to g-1
// 2. Reverse A, Reverse B, Reverse a[]
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
