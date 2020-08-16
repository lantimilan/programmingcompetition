// timber.cc
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// bleft[pos] is the longest streak from bleft of pos
// gright[pos] is the longest streak from gright of pos
//
// pos could be P[i] or P[i]-H[i] (fall left) or P[i]+H[i] (fall gright)
// 
// to compute bleft[pos], we can scan trees from left to right, consider tree[i]
// if we push tree[i] to its right, then for pos = P[i]+H[i]
// we have bleft[pos] = bleft[P[i]] + H[i] if bleft[pos] is not defined
// note that the first time we set bleft[pos], it is the optimal value for pos
// similarly,
// to compute gright[pos], we scan trees from gright to bleft
// for pos = P[i]-H[i]
// gright[pos] = gright[P[i]] + H[i]
//
// ans is just best of bleft[pos] + gright[pos] among all pos
//

void chmax(int& a, int b) {
  if (a < b) a = b;
}

void solve() {
  int N; cin >> N;
  vector<pair<int, int>> trees(N);  // (position, height)
  map<int, int> bleft, gright;
  for (int i = 0; i < N; ++i) {
    cin >> trees[i].first >> trees[i].second;
  }
  sort(trees.begin(), trees.end());

  vector<int> position(N), height(N);
  for (int i = 0; i < N; ++i) {
    position[i] = trees[i].first;
    height[i] = trees[i].second;
  }
  bleft[position[0]] = 0;
  for (int i = 0; i < N; ++i) {
    int pos = position[i];
    int ht = height[i];
    int newpos = pos + ht;  // push tree[i] to right
    int newval = ht + bleft[pos];
    if (newval > bleft[newpos]) {
      bleft[newpos] = newval;
    }
  }
  gright[position[N-1]] = 0;
  for (int i = N-1; i >= 0; --i) {
    int pos = position[i];
    int ht = height[i];
    int newpos = pos - ht;  // push tree[i] to left
    int newval = ht + gright[pos];
    if (newval > gright[newpos]) {
      gright[newpos] = newval;
    }
  }

  int ans = 0;
  for (const pair<int, int>& kv : bleft) {
    int pos = kv.first;
    int l = kv.second;
    int r = gright[pos];
    chmax(ans, l + r);
  }
  for (const pair<int, int>& kv : gright) {
    int pos = kv.first;
    int r = kv.second;
    int l = bleft[pos];
    chmax(ans, l + r);
  }
  cout << ans << endl;
}

int main() {
  int T; cin >> T;
  for (int t = 1; t <= T; ++t) {
    cout << "Case #" << t << ": ";
    solve();
  }
}
