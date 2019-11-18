#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll MOD = 1000000007;
constexpr ll MAXN = 1000005;

ll F[MAXN];
ll invF[MAXN];

ll modpow(ll base, ll exp) {
  ll res = 1;
  ll basePower = base;
  for (ll k = 1; k <= exp; k <<= 1) {
    if ((k & exp) > 0) {
      res = (res * basePower) % MOD;
    }
    basePower = (basePower * basePower) % MOD;
  }
  return res;
}

ll nPr(int n, int r) {
  assert(r <= n);
  ll res = 1;
  res = (res * F[n]) % MOD;
  res = (res * invF[n - r]) % MOD;
  return res;
}

int main() {
  int N;
  cin >> N;
  F[0] = 1;
  invF[0] = 1;
  for (int i = 1; i <= N; i++) {
    F[i] = (F[i - 1] * i) % MOD;
    invF[i] = modpow(F[i], MOD - 2);
  }
  ll res = 0;
  for (int i = 1; i <= N; i++) {
    ll cur = 1;
    cur = (cur * nPr(N, i)) % MOD;
    cur = (cur * (i + 1)) % MOD;
    cur = (cur * i) % MOD;
    res = (res + cur) % MOD;
  }
  cout << res << endl;
  return 0;
}
