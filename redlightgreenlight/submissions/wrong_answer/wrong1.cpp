// WA - Not enough precision on Binary Search

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<double, int> frame;
static constexpr int MAXN = 100005;

int n, m;
double T;
vector<pair<int, int>> graph[MAXN];
double l[MAXN], g[MAXN], r[MAXN], t[MAXN];
bool visited[MAXN];

bool p(double speed) {
    priority_queue<frame, vector<frame>, greater<frame>> pq;
    for (int i = 0; i <= n; i++) {
        visited[i] = false;
    }
    pq.push(make_pair(0.0, 1));
    while (!pq.empty()) {
        frame f = pq.top();
        pq.pop();
        int node = f.second;
        double time = f.first;
        if (node == n) {
            return true;
        }
        if (visited[node]) {
            continue;
        }
        visited[node] = true;
        for (pair<int, int> edge : graph[node]) {
            int v = edge.first;
            int id = edge.second;
            double period = g[id] + r[id];
            double dt = l[id] / speed;
            double start = time;
            if (time < t[id]) {
                start = t[id];
            } else {
                int num_periods = (int) ((time - t[id]) / period); 
                double period_start = t[id] + period * num_periods;
                if (time > period_start + g[id]) {
                    start = period_start + period;
                }
            }
            if (start + dt <= T) {
                pq.push(make_pair(start + dt, v));
            }
        }
    }
    return false;
}

int main() {
    cin.sync_with_stdio(0); cin.tie(0);
    cin.exceptions(cin.failbit);

    scanf(" %d %d %lf", &n, &m, &T);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf(" %d %d %lf %lf %lf %lf", &u, &v, &l[i], &g[i], &r[i], &t[i]);
        graph[u].push_back(make_pair(v, i));
    }

    double lo = 0;
    double hi = 1;
    while (!p(hi)) {
        hi *= 2;
    }
    while (lo + 1e-5 < hi) {
        double mid = (lo + hi) / 2.0;
        if (p(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    printf("%lf\n", hi);
}
