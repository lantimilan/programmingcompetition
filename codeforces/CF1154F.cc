// CF1154F.cc
#include <algorithm>
#include <iostream>
using namespace std;

// note that we only need k cheapest items, and k <= 2000
// sort a[] and keep only the smallest k items
// now let dp[n] be the cost to buy n items
// dp[0] = 0
// dp[n] = dp[n-x_j] + a[n-1,...n-t_j] where offer (x_j, y_j) and t_j = x_j-y_j
// n is at most 2000 and m is at most 2*10^5
// we only need to keep the best offer with same xj, e.g. if two offers
// (10, 9) and (10, 5), then we only keep (10, 9)
// for that we only keep 2000 offers with xj = 1 to 2000

int A[200000+5];
int dp[2005];
int pre[2005];
int offer[2005];

template <typename T>
void chmin(T& a, T b) {
    if (a > b) a = b;
}

int main() {
    int n, m, k; cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) cin >> A[i];
    sort(A, A + n);
    n = k;

    pre[0] = 0;
    for (int i = 0; i < k; ++i) {
        pre[i+1] = pre[i] + A[i];
    }

    for (int i = 0; i < m; ++i) {
        int xj, yj; cin >> xj >> yj;
        if (xj <= 2000) {
            if (offer[xj] < yj) {
                offer[xj] = yj;
            }
        }
    }

    dp[0] = 0;
    for (int l = 1; l <= n; ++l) {
        dp[l] = dp[l-1] + A[l-1];
        for (int xj = 1; xj <= l; ++xj) {
            int yj = offer[xj], tj = xj - yj;
            int extra = pre[l] - pre[l-tj]; // A[l-1,l-2,..,l-t_j]
            int cost = dp[l-xj] + extra;
            chmin(dp[l], cost);
        }
    }
    cout << dp[n] << endl;
}
