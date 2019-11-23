#include <bits/stdc++.h>

using namespace std;
using ll = long long;

map<string, vector<pair<string, int>>> G;
unordered_map<string, map<string, int>> dp;

map<string, int> solve(string& s) {
  if (dp.find(s) != dp.end()) {
    return dp[s];
  }
  map<string, int> res;
  if (G[s].size() == 0) {
    res[s] = 1;
    return dp[s] = res;
  }
  for (const auto& nxt : G[s]) {
    string p = nxt.first;
    int c = nxt.second;
    for (const auto& pr : solve(p)) {
      res[pr.first] += c * pr.second;
    }
  }
  return dp[s] = res;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string x;
    int m;
    cin >> x >> m;
    for (int j = 0; j < m; j++) {
      int c;
      string y;
      cin >> c >> y;
      G[x].emplace_back(y, c);
    }
  }
  string s;
  cin >> s;
  for (const auto& p : solve(s)) {
    cout << p.first << ' ' << p.second << '\n';
  }
  return 0;
}
