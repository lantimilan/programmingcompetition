// alchemy.cc
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

void solve() {
  // we only need to count num of A and B and answer is yes if the count diff by one
  // proof by induction, a seq becomes smaller after fusing a triple with A adjacent to B
  int N; cin >> N;
  string s; cin >> s;
  int cnt[2] = {0};
  for (char ch : s) {
    int x = (ch == 'A' ? 0 : 1);
    cnt[x]++;
  }
  int d = abs(cnt[0] - cnt[1]);
  cout << (d == 1 ? 'Y' : 'N') << endl;
}

int main() {
  int T; cin >> T;
  for (int t = 1; t <= T; ++t) {
    cout << "Case #" << t << ": ";
    solve();
  }
}
