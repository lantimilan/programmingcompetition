// CF1154G.cc
#include <cassert>
#include <iostream>
#include <map>
using namespace std;

// find two elements with minimum lcm in an array of size 10^6, a[i] max 10^7
// solution:
// we can enumerate all possible gcd with g = 1, 2, 3, ..., a_max
// for each g, we can scan all possible multiples g, 2g, 3g, ...
// to look for a pair of elements in a[]
// Now the time complexity is a_max * (1 + 1/2 + 1/3 + ... + 1/a_max)
// or a_max * H(a_max) = a_max * log (a_max)

constexpr int Amax = 1e7+5;
int A[Amax];
// map<int, int> freq;  // (value, cnt), array is much faster than RBtree map
int freq[Amax];  // global initialize to zero
int N;

int main() {
    // boilerplate for fast c++ io.
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        freq[A[i]]++;
    }

    long long best = 1LL * Amax * Amax;
    int val1 = -1, val2 = -1;

    for (int g = 1; g < Amax; ++g) {
    // cout << g << endl;
    int a = -1, b = -1;
    for (int k = g; k < Amax; k += g) {
        int fr = freq[k];
        while (fr > 0 && b < 0) {
            if (a < 0) { a = k; --fr; }
            else if (b < 0) { b = k; --fr; }
        }
        if (a > 0 && b > 0) {
            assert(a % g == 0);
            assert(b % g == 0);
            long long curr = 1LL * a * b / g;
            if (curr < best) {
                best = curr;
                val1 = a;
                val2 = b;
            }
            break;
        }
    }
    }
    // cout << val1 << ' ' << val2 << endl;
    int x1 = -1, x2 = -1;
    for (int i = 0; i < N; ++i) {
        if (x1 < 0 && val1 == A[i]) {
            x1 = i;
        } else if (x2 < 0 && val2 == A[i]) {
            x2 = i;
        }
    }
    if (x1 > x2) {
        swap(x1, x2);
    }
    cout << (x1+1) << ' ' << (x2+1) << endl;
}
