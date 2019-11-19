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

int N;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(10);

    cin >> N;

    ll res = 0, p = 1;
    for (ll i = 1; i <= N; i++) {
        p = p * (N - i + 1) % MOD;
        res = (res + (i + 1) * i % MOD * p % MOD) % MOD;
    }
    cout << res << "\n";

    return 0;
}
