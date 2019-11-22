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

int N, M, H, ht[200][200], use[200][200], vis[200][200], ab[200][200], lft[200], rgt[200];

void flood(int r, int c, int h) {
    if (r < 0 || c < 0 || r >= N || c >= M) return;
    if (vis[r][c]) return;
    vis[r][c] = 1;
    if (ht[r][c] <= h)
        use[r][c] = 1;
    else return;
    flood(r - 1, c, h);
    flood(r + 1, c, h);
    flood(r, c - 1, h);
    flood(r, c + 1, h);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(10);
    // freopen("../../data/secret/02.in", "r", stdin);

    cin >> N >> M >> H;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> ht[i][j];

    for (int i = 0; i <= H; i++) {
        fill(vis[0], vis[199] + 200, 0);
        flood(N / 2, M / 2, i);
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                ab[r][c] = use[r][c];
                if (r > 0 && use[r][c]) ab[r][c] += ab[r-1][c];
            }
        }
        int ans = 0;
        for (int r = 0; r < N; r++) {
            vector<pair<int, int>> st;
            for (int c = 0; c < M; c++) {
                while (st.size() && st.back().x >= ab[r][c]) st.pop_back();
                if (st.size()) lft[c] = st.back().y;
                else lft[c] = -1;
                st.push_back({ab[r][c], c});
            }
            st.clear();
            for (int c = M - 1; c >= 0; c--) {
                while (st.size() && st.back().x >= ab[r][c]) st.pop_back();
                if (st.size()) rgt[c] = st.back().y;
                else rgt[c] = M;
                st.push_back({ab[r][c], c});
            }
            for (int c = 0; c < M; c++)
                ans = max(ans, (rgt[c] - lft[c] - 1) * ab[r][c]);
        }
        cout << ans << "\n";
    }

    return 0;
}
