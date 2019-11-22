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

int cdp[13][13][13][13];

int check(int x, int y, int z, int w) {
  if (cdp[x][y][z][w] != -1) {
    return cdp[x][y][z][w];
  }
  int& res = cdp[x][y][z][w];
  if (z == w) {
    return res = 0;
  }
  if (isA(x) && isA(y) && isA(z) && isA(w)) {
    return res = 0;
  }
  if (isB(x) && isB(y) && isB(z) && isB(w)) {
    return res = 0;
  }
  return res = 1;
}

ll dp[10005][13][13][13];

ll solve(int N, int x, int y, int z) {
  if (N == 0) {
    return 1;
  }
  if (dp[N][x][y][z] != -1) {
    return dp[N][x][y][z];
  }
  ll res = 0;
  for (int i = 0; i < 12; i++) {
    if (!check(x, y, z, i)) {
      continue;
    }
    res = (res + solve(N - 1, y, z, i)) % MOD;
  }
  return dp[N][x][y][z] = res;
}

int main() {
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 13; j++) {
      for (int k = 0; k < 13; k++) {
        for (int l = 0; l < 13; l++) {
          cdp[i][j][k][l] = -1;
        }
      }
    }
  }
  for (int i = 0; i < 10005; i++) {
    for (int j = 0; j < 13; j++) {
      for (int k = 0; k < 13; k++) {
        for (int l = 0; l < 13; l++) {
          dp[i][j][k][l] = -1;
        }
      }
    }
  }
  int N;
  cin >> N;
  cout << solve(N, 12, 12, 12) << endl;
  return 0;
}
