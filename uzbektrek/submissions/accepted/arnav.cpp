#include <bits/stdc++.h>

using namespace std;

using ll = long long;

constexpr int MOD = 1e9 + 7;
int p;

map<int, int> memo;

int solve(int n) {
    if (n % p != 0) {
        return solve(n - (n % p));
    }

    if (n == 0) {
        return 1;
    }

    auto it = memo.find(n);
    if (it != end(memo))
        return it->second;

    int res = solve(n / p) + solve(n - p);
    if (res >= MOD)
        res -= MOD;

    return memo[n] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n;
    cin >> n >> p;

    cout << solve(n) << '\n';
    
    return 0;
}
