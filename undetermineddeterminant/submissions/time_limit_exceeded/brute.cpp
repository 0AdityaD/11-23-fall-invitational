#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int MAX_N = 1000100;
constexpr int MOD = 998244353;

int n;
int arr[MAX_N];

int ans;
int denom;

int deg[MAX_N];

int modpow(int b, int e) {
    if (e == 0) return 1;
    ll x = modpow(b, e >> 1);
    x = (x * x) % MOD;
    if (e & 1) x = (x * b) % MOD;
    return (int) x;
}

int modinv(int x) {
    return modpow(x, MOD - 2);
}

int determinant(vector<vector<int>> &a) {
    ll res = 1;
    for (int i = 0; i < n; ++i) {
        int b = i;
        for (int j = i + 1; j < n; ++j) {
            if (abs(a[j][i]) > abs(a[b][i])) b = j;
        }

        if (i != b) swap(a[i], a[b]), res = (1LL*res*(-1+MOD))%MOD;
        res = 1LL * res * a[i][i] % MOD;
        if (res == 0) return 0;
        for (int j = i + 1; j < n; ++j) {
            ll mult = 1LL * a[j][i] * modinv(a[i][i]) % MOD;
            if (mult != 0) for (int k = i + 1; k < n; ++k) a[j][k] = (a[j][k] - 1LL * mult * a[i][k] % MOD + MOD) % MOD;
        }
    }

    return (int) res;
}

void solve_one() {
    vector<vector<int>> mat(n, vector<int>(n));

    for (int i = 0; i < n; ++i) {
        deg[i] = 1;
    }

    for (int i = 0; i < n - 2; ++i) {
        ++deg[arr[i]];
    }

    for (int i = 0; i < n - 2; ++i) {
        for (int j = 0; j < n; ++j) {
            if (deg[j] == 1) {
                mat[arr[i]][j] = 1;
                mat[j][arr[i]] = 1;
                --deg[j];
                --deg[arr[i]];
                break;
            }
        }
    }

    int u = -1, v = -1;
    for (int i = 0; i < n; ++i) {
        if (deg[i] == 1) {
            if (u == -1) u = i;
            else v = i;
            --deg[i];
        }
    }

    mat[u][v] = 1;
    mat[v][u] = 1;

    ans = (0LL + ans + determinant(mat) + MOD) % MOD;
    denom = (denom + 1) % MOD;
}

void solve(int idx) {
    if (idx == n - 2) {
        solve_one();
    } else {
        for (int i = 0; i < n; ++i) {
            arr[idx] = i;
            solve(idx + 1);
        }
    }
}

int main() {
    scanf(" %d", &n);

    if (n == 1) printf("0\n");
    else {
        solve(0);

        printf("%d\n", (int) (1LL * ans * modinv(denom) % MOD));
    }

    return 0;
}
