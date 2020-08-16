// CF1153E.cc
#include <cassert>
#include <iostream>
using namespace std;

// scan row by row, if we found two rows with odd results, then each row has
// one head/tail.
// else scan col by col, and we must found two cols with odd results.
// Now consider one row with one head/tail
// row[k, 1..n]
// sum(1..n) is odd, then we binary search, sum(1..n/2) and sum(n/2..n), one of
// them must be odd and we can recurse on the odd part.
// total number of query:
// case 1: (r1, c1) (r2, c2) with r1 != r2 and c1 != c2
// 1000 + log(1000) + log(1000) = 1000 + 10 + 10 = 1020
// case 2: r1 == r2 or c1 == c2
// 1000 + 1000 + log(1000) = 2010
// within 2019 bound.

int query(int r1, int c1, int r2, int c2) {
    cout << "? ";
    cout << (r1+1) << " " << (c1+1) << " " << (r2+1) << " " << (c2+1);
    cout << endl << flush;
    int ans; cin >> ans;
    return ans;
}

// search row or col, assume sum is odd in that row or col
// returns the head/tail position, zero-based
int searchrow(int r, int c1, int c2) {
    // cout << "searchrow " << r << " " << c1 << " " << c2 << endl << flush;
    while (c1 + 1 < c2) {
        int m = (c1 + c2) / 2;
        if (query(r, c1, r, m-1) &1) {
            c2 = m;
        } else {
            c1 = m;
        }
    }
    return c1;
}

int searchcol(int c, int r1, int r2) {
    // cout << "searchcol " << c << " " << r1 << " " << r2 << endl << flush;
    while (r1 + 1 < r2) {
        int m = (r1 + r2) / 2;
        if (query(r1, c, m-1, c) &1) {
            r2 = m;
        } else {
            r1 = m;
        }
        // cout << "searchcol " << c << " " << r1 << " " << r2 << endl << flush;
    }
    return r1;
}

int main() {
    int n; cin >> n;
    // row scan
    int r1 = -1, r2 = -1, c1 = -1, c2 = -1;
    for (int i = 0; i < n; ++i) {
        int ans = query(i, 0, i, n-1);
        if (ans & 1) {
            if (r1 < 0) r1 = i;
            else r2 = i;
        }
    }
    // cout << "row scan done: " << r1 << " " << r2 << endl << flush;
    if (r1 < 0) {  // head/tail in the same row, check col
        for (int j = 0; j < n; ++j) {
            int ans = query(0, j, n-1, j);
            if (ans & 1) {
                if (c1 < 0) c1 = j;
                else c2 = j;
            }
        }
        // cout << "col scan down: " << c1 << " " << c2 << endl << flush;
        assert(c1 >= 0 && c2 >= 0);
        r1 = r2 = searchcol(c1, 0, n);
        // r2 = searchcol(c2, 0, n);
    } else {
        c1 = searchrow(r1, 0, n);
        c2 = searchrow(r2, 0, n);
    }
    cout << "! " << (r1+1) << " " << (c1+1) << " " << (r2+1) << " "
        << (c2+1) << endl << flush;
}
