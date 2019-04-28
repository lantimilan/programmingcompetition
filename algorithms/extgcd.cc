// extgcd.cc
// extended euclidean algorithm, given positive integer a, b
// return x, y and g such that a * x + b * y = g
// note that x and y may be negative
#include <cassert>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int extgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    int q = a / b, r = a % b;
    int x1, y1;
    int g = extgcd(b, r, x1, y1);
    x = y1, y = x1 - q * x;
    return g;
}

int main() {
    vector<pair<int,int>> pairs = {{1, 3},
        {12, 18},
        {123, 9},
        {14, 7},
        {51, 26},
        {12, 8}};

    for (const pair<int,int>& p : pairs) {
        int a = p.first, b = p.second;
        int x, y;
        int g = extgcd(a, b, x, y);
        cout << a << " * " << x << " + " << b << " * " << y << " = " << g
             << endl;
        assert(a * x  + b * y == g);
    }
    /*
    int a, b;
    while (cin >> a >> b) {
        int x, y;
        int g = extgcd(a, b, x, y);
        cout << a << " * " << x << " + " << b << " * " << y << " = " << g
             << endl;
        assert(a * x  + b * y == g);
    }
    */
}

