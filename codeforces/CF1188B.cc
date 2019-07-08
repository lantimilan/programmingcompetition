// CF1188B.cc
#include <iostream>
#include <map>
using namespace std;

int a[300000+5];
map<int, int> cnts;

int main() {
    int n, p, k; cin >> n >> p >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        int v = a[i];
        // hash by a^4 - a*k because a[i] != a[j], the original condition
        // can be transformed by multiply both sides by (a[i] - a[j])
        int key = 1LL * v * v % p * v % p * v % p - 1LL * v * k % p;
        if (key < 0) key += p;
        cnts[key]++;
    }

    long long total = 0;
    for (const auto& kv : cnts) {
        int key = kv.first;
        int value = kv.second;
        // value choose 2
        total += 1LL * value * (value -1) / 2;
    }
    cout << total << endl;
}
