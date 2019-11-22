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

struct Edge {
    int u, v, d, g, r, t;
};
int N, M, T;
vector<Edge> adj[50010];

bool time(ld sp) {
    priority_queue<pair<ld, int>, vector<pair<ld, int>>, greater<pair<ld,int>>> pq;
    vector<ld> dist(N + 1, INF);
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto t = pq.top(); pq.pop();
        if (dist[t.second] < t.first) continue;
        if (t.second == N)
            return t.first <= T;
        for (auto e : adj[t.second]) {
            int s = floor(t.first);
            s = (s - e.t + e.g + e.r) % (e.g + e.r);
            ld wait = 0;
            if (s >= e.g) wait += e.r - (s - e.g) - (t.first - floor(t.first));
            ld d = e.d / sp;
            if (dist[e.v] > dist[e.u] + wait + d) {
                dist[e.v] = dist[e.u] + wait + d;
                pq.push({dist[e.v], e.v});
            }
        }
    }
    return false;
}

ld solve() {
    ld lo = 0, hi = 1e9;
    while (hi - lo > EPS) {
        ld m = (hi + lo) / 2;
        bool w = time(m);
        if (w) hi = m;
        else lo = m;
    }
    return (lo + hi) / 2;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(8);

    cin >> N >> M >> T;
    for (int i = 0; i < M; i++) {
        int u, v, d, g, r, t;
        cin >> u >> v >> d >> g >> r >> t;
        adj[u].push_back(Edge{u,v,d,g,r,t});
    }

    cout << solve() << "\n";

    return 0;
}
