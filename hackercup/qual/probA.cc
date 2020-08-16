// probA.cc
#include <iostream>
#include <vector>
using namespace std;

void solve() {
  int N; cin >> N;
  string in; cin >> in;
  string out; cin >> out;

  vector<vector<int>> conn(N, vector<int>(N, 0));
  for (int i = 0; i < N; ++i) {
    conn[i][i] = 1;
    if (i+1 < N && out[i] == 'Y' && in[i+1] == 'Y') {
      conn[i][i+1] = 1;
    }
    if (i-1 >= 0 && out[i] == 'Y' && in[i-1] == 'Y') {
      conn[i][i-1] = 1;
    }
  }

  for (int k = 0; k < N; ++k) if (in[k] == 'Y' && out[k] == 'Y') {
    for (int i = 0; i < N; ++i) if (i != k) { 
      for (int j = 0; j < N; ++j) if (j != i && j != k) {
        conn[i][j] |= (conn[i][k] & conn[k][j]);
      }
    }
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cout << (conn[i][j] ? 'Y' : 'N');
    }
    cout << endl;
  }
}

int main() {
  int T; cin >> T;
  for (int t = 1; t <= T; ++t) {
    cout << "Case #" << t << ": " << endl;
    solve();
  }
}
