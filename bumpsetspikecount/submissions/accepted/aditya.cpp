#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll MOD = 1000000007;

bool notE(int x) {
  return x != 12;
}

bool isA(int x) {
  return notE(x) && x < 6;
}

bool isB(int x) {
  return notE(x) && x >= 6;
}

int cdp[13][13][13];

int check(int x, int y, int z) {
  if (cdp[x][y][z] != -1) {
    return cdp[x][y][z];
  }
  int& res = cdp[x][y][z];
  if (y == z) {
    return res = 0;
  }
  if (isA(x) && isA(y) && isA(z)) {
    return res = 0;
  }
  if (isB(x) && isB(y) && isB(z)) {
    return res = 0;
  }
  return res = 1;
}

ll dp[50005][13][13];

ll solve(int N, int x, int y) {
  if (N == 0) {
    return 1;
  }
  if (dp[N][x][y] != -1) {
    return dp[N][x][y];
  }
  ll res = 0;
  for (int i = 0; i < 12; i++) {
    if (!check(x, y, i)) {
      continue;
    }
    res = (res + solve(N - 1, y, i)) % MOD;
  }
  return dp[N][x][y] = res;
}

int main() {
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 13; j++) {
      for (int k = 0; k < 13; k++) {
        cdp[i][j][k] = -1;
      }
    }
  }
  for (int i = 0; i < 50005; i++) {
    for (int j = 0; j < 13; j++) {
      for (int k = 0; k < 13; k++) {
        dp[i][j][k] = -1;
      }
    }
  }
  int N;
  cin >> N;
  cout << solve(N, 12, 12) << endl;
  return 0;
}
