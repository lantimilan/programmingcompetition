// CF1151F.cc
// <bits/stdc++.h> the GCC catch all header for std
#include <iostream>
using namespace std;

constexpr int MOD = 1e9+7;

template <int M>
class modnum {
public:
    explicit modnum(int v) : v_(v) {}

    using ll = long long;
    modnum& operator+=(modnum r) {
        v_ += r.v;
        if (v_ >= M) v -= M;
        return *this;
    }
    modnum& operator-=(modnum r) {
        v_ -= r.v;
        if (v_ < 0) v_ += M;
        return *this;
    }
    modnum& operator*=(modnum r) {
        v_ = ll(v_) * r % M;
        return *this;
    }
    modnum& operator/=(modnum r) {
    }
private:
    int v_;
};

class Matrix {
public:
private:
    vector<vector<int>> data;
};


// Use a row and a matrix to iterate
// [next_row] = [curr_row] * trans_mat
// Let p = cnt[0] and q = cnt[1]
// Let m = min(p, q)
// A state is the number of 1's in a[0..p)
// So the end state we seek is dp[0]
// curr_row = [p0 p1 p2 ... p_m]
// trans_mat = |same0  plus0                    |
//             |minus1 same1  plus1             |
//             |       minus2 same2 plus2       |
//             |            ...                 |
//             |                 minus_m same_m |
// Call a[0..p) L and a[p..n) R
// at state (l, t), it has three next states
// here l is the number of 1's in a[0..p), notice that the number of 0's in
// a[p..n) is also l. Why? a[0..n) has p of 0's and q of 1's, and then we move
// l of 1's from R to L, as a result, there are exactly l of 0's from L to R
// Now the probability of the three outcomes, all probability below will be
// divided by (n choose 2) because that is all possible (i,j) pairs
// 1) swap a 1 from L with a 0 from R, then (l-1, t+1) occurs with pr = l*l
// 2) swap a 0 from L with a 1 from R, then (l+1, t+1) occurs with
// pr = (p-l)*(q-l)
// 3) otherwise (l, t+1) occurs with remaining probability, 1.0 - pr_1 - pr_2
//
// implementation:
// We need two things:
// 1. arithmetic operations w.r.t. MOD=1e9+7
// 1.1 the only tricky bit is division, or inv, which can be done with either
// extended euclidean or fast expo to M-2
// 2. matrix multiplication and fast exponentiation
int main() {
}
