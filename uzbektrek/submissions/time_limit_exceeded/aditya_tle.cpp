#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll MOD = 1000000007;

ll n, p;

ll solve(ll x) {
  if (x == 0) {
    return 1;
  }
  if (x % p > 0) {
    return solve(x / p * p);
  }
  return (solve(x / p) + solve(x - p)) % MOD;
}

int main() {
  cin >> n >> p;
  cout << solve(n) << endl;
  return 0;
}
