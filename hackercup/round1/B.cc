// B.cc
#include <algorithm>
#include <iostream>
using namespace std;

int P[1000000+5]; // N drivers
int Q[1000000+5]; // M logs
int N, M, K, S;

void input() {
  cin >> N >> M >> K >> S;
  for (int i = 0; i < K; ++i) cin >> P[i];
  int A, B, C, D;
  cin >> A >> B >> C >> D;
  for (int i = K; i < N; ++i) {
    P[i] = (1LL * A * P[i-2] % D + 1LL * B * P[i-1] % D + C) % D + 1;
  }
  for (int i = 0; i < K; ++i) cin >> Q[i];
  cin >> A >> B >> C >> D;
  for (int i = K; i < M; ++i) {
    Q[i] = (1LL * A * Q[i-2] % D + 1LL * B * Q[i-1] % D + C) % D + 1;
  }

  /*
  cout << "drivers: ";
  for (int i = 0; i < N; ++i) cout << P[i] << " "; cout << endl;
  cout << "logs: ";
  for (int i = 0; i < M; ++i) cout << Q[i] << " "; cout << endl;
  */
}

bool check(long long m) {
  int start = 0;  // leftmost index of logs to pick up
  for (int i = 0; i < N; ++i) {
    if (start >= M) return true;
    long long budget = m;
    int pos = P[i];
    // let [start..newstart-1] be set of logs assigned to driver[i]
    // p1 = Q[start], p2 = Q[newstart-1]
    // then the cost is
    // 1. pos <= p1, then cost = p2 - p1 + abs(pos - p1)
    // 2. p1 < pos < p2, then cost = p2 - p1 + min(abs(pos-p1), abs(pos-p2))
    // 3. p2 <= pos, then cost = p2 - p1 + abs(pos - p2)
    // This formula works for all three cases:
    // cost = p2 - p1 + min(abs(pos-p1), abs(pos-p2))
    int newstart = start;
    while (newstart < M) {
      int p1 = Q[start];
      int p2 = Q[newstart];
      long long d1 = abs(pos - p1);
      long long d2 = abs(pos - p2);
      long long cost = p2 - p1 + std::min(d1, d2);
      if (cost > budget) break;
      else newstart++;
    }
    start = newstart;
  }
  return start >= M;
}

void solve() {
  input();
  sort(P, P+N);
  sort(Q, Q+M);

  long long lo = -1, hi = 1LL << 50;
  // bsearch
  while (lo + 1 < hi) {
    long long m = (lo + hi) / 2;
    if (check(m)) hi = m;
    else lo = m;
  }
  // ans is hi
  cout << hi << endl;
}

int main() {
  int T; cin >> T;
  for (int t = 1; t <= T; ++t) {
    cout << "Case #" << t << ": ";
    solve();
  }
}
