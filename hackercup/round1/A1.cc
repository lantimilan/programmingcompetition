// A1.cc
#include <iostream>
using namespace std;

int L[1000000+5];
int H[1000000+5];

void solve() {
  const int MOD = 1e9+7;
  
  int N, K, W; cin >> N >> K >> W;
  for (int i = 0; i < K; ++i) cin >> L[i];
  long long AL, BL, CL, DL; cin >> AL >> BL >> CL >> DL;
  for (int i = K; i < N; ++i) {
    L[i] = (AL * L[i-2] % DL + BL * L[i-1] % DL + CL) % DL + 1;
  }
  for (int i = 0; i < K; ++i) cin >> H[i];
  long long AH, BH, CH, DH; cin >> AH >> BH >> CH >> DH;
  for (int i = K; i < N; ++i) {
    H[i] = (AH * H[i-2] % DH + BH * H[i-1] % DH + CH) % DH + 1;
  }
  cout << "L[1..N]=";
  for (int i = 0; i < N; ++i) {
    cout << L[i] << " ";
  } cout << endl;
  cout << "H[1..N]=";
  for (int i = 0; i < N; ++i) {
    cout << H[i] << " ";
  } cout << endl;

  long long p1 = 2 * (W + H[0]);
  long long prod = p1;
  cout << "p1=" << p1 << endl;
  for (int i = 1; i < N; ++i) {
    if (L[i-1] + W < L[i]) {
      p1 = (p1 + (W + H[i]) * 2LL);
    } else {
      if (H[i] <= H[i-1]) {
        p1 = p1 + 2LL * (L[i]- L[i-1]);
      } else {
        p1 = p1 - (H[i-1] + (L[i-1]+W-L[i]) * 2LL) + H[i] - H[i-1] + W + H[i] + L[i] - L[i-1];
      }
    }
    p1 %= MOD;
    cout << "p1=" << p1 << endl;
    prod = prod * p1 % MOD;
  }
  cout << prod << endl;
}

int main() {
  int T; cin >> T;
  for (int t = 1; t <= T; ++t) {
    cout << "Case #" << t << ": ";
    solve();
  }
}
