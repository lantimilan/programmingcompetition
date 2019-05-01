// extgcd.cc
// extended euclidean algorithm, given positive integer a, b
// return x, y and g such that a * x + b * y = g
// note that x and y may be negative
#include <cassert>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// given positive integer a and b, find integer x and y (maybe negative)
// such that a * x + b * y = g where g is gcd(a, b)
// notice that one of x and y is negative because a >= g and b >= g
// in our implementation we ensure x > 0, then y <= 0
//
// let a = q * b + r
// then if we know the x1 and y1 such that b * x1 + r * y1 = g
// then substitue in r, we have
// b * x1 + (a - q * b) * y1 = g
// regrouping by a and b, we have
// a * y1 + b * (x1 - q * y1) = g
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

// Given positive integer a and m such that a and m coprime, that is,
// gcd(a, m) = 1, find the multiplicative inverse of a modulo m, that is,
// find a' such that a * a' = 1 (mod m) with 0 < a' < m
// this multiplicative inverse, if exists, is unique.
// We could use the above extgcd to find a', but now we have an implementation
// optimization.
// Note that we only need x in a * x + m * y = 1, and we do not need y.
// Let a = q * m + r and suppose we have found x1 and y1 such that
// m * x1 + r * y1 = 1, now substitute in r = a - q * m, we have
// m * x1 + (a - q * m) * y1 = 1
// a * y1 + (x1 - q * y1) * m = 1
// Notice that the above implies a * y1 = 1 (mod m), so y1 is the inverse and
// we just need to make y1 fit into 0 < y1 < m
// But we only keep track of x1, not y1? Here is a way to get y1 from x1
// y1 = (1 - m * x1) / r
// this 1 - m * x1 is actually a multiple of r and this integer division yields
// zero as remainder. So a recursive impl would be
// if a == 1, then return 1
// else:
// r = a % m
// x1 = inv(m, r)
// t = (1 - m * x1) / r
// t = t % m
// if t < 0 then t += m
// ?? can we do better, do we know that -m < t < 0?
int inv(int a, int m) {

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

