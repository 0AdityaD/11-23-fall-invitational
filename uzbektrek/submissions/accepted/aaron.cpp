#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll INF = 1e18;
const int MOD = 1000000007;
const ld EPS = 1e-9;
const ld PI = acos(-1);

#define x first
#define y second

int N, P, dp[10000010];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(10);

    cin >> N >> P;

    dp[0] = 1;

    int n = N / P;

    long long p = 1;
    while (p <= n) {
        for (int i = p; i <= n; i++)
            dp[i] = (dp[i] + dp[i - p]) % MOD;
        p *= P;
    }

    long long res = 0;
    for (int i = 0; i <= n; i++)
        res = (res + dp[i]) % MOD;
    cout << res << "\n";

    return 0;
}
