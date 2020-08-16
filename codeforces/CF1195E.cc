// CF1195E.cc
#include <iostream>
#include <queue>
#include <utility>
using namespace std;

int n, m, a, b;
int mat[3005][3005];
int rmin[3005][3005];
int g[3005 * 3005];

// populate rmin[0][col] to rmin[n-1][col]
// each rmin[i][j] = min{mat[i-a+1][j],.., mat[i][j]}
void populate(int col) {
    deque<pair<int,int>> que;  // (value, pos)
    for (int i = 0; i < n; ++i) {
        int val = mat[i][col];
        int last = i - a;
        // pop front elems that are too far in the past
        while (!que.empty() && que.front().second <= last) {
            que.pop_front();
        }
        // pop back elems that are no better
        while (!que.empty() && que.back().first >= val) {
            que.pop_back();
        }
        que.push_back(make_pair(val, i));
        rmin[i][j] = que.front().first;
    }
}

int main() {
    cin >> n >> m >> a >> b;
    int x, y, z; cin >> g[0] >> x >> y >> z;

    for (int i = 1; i < n * m; ++i) {
        g[i] = 1LL * g[i-1] * x + y % z;
    }
    for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
        int index = (i-1) * m + j-1;
        h[i-1][j-1] = g[index];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cout << h[i][j] << ' ';
        }
        cout << endl;
    }

    for (int j = 0; j < m; ++j) {
        populate(j);
    }
}
