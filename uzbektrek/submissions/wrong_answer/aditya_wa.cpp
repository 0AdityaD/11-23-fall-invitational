#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll MOD = 1000000007;

ll n, p;
unordered_map<ll, ll> dp;

ll solve(ll x) {
  if (x == 0) {
    return 1;
  }
  if (dp.find(x) != dp.end()) {
    return dp[x];
  }
  if (x % p > 0) {
    return solve(x / p * p);
  }
  return dp[x] = (solve(x / p) + solve(x - p));
}

int main() {
  cin >> n >> p;
  cout << solve(n) << endl;
  return 0;
}
