#include <bits/extc++.h>

using namespace std;
using ll = long long;
using vll = vector<ll>;
using vi = vector<int>;

constexpr int MAXN = 505;
constexpr int MAXM = 105;

int N, M;
int G[MAXN][MAXN];
int P[MAXM];
int F[MAXM];

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()

typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

constexpr ll INF = numeric_limits<ll>::max() / 4;
typedef vector<ll> VL;

struct MCMF {
  int N;
  vector<vi> ed, red;
  vector<VL> cap, flow, cost;
  vi seen;
  VL dist, pi;
  vector<pii> par;

  MCMF(int N)
    : N(N), ed(N), red(N), cap(N, VL(N)), flow(cap), cost(cap), seen(N),
      dist(N), pi(N), par(N) {}

  void addEdge(int from, int to, ll cap, ll cost) {
    this->cap[from][to] = cap;
    this->cost[from][to] = cost;
    ed[from].push_back(to);
    red[to].push_back(from);
  }

  void path(int s) {
    fill(all(seen), 0);
    fill(all(dist), INF);
    dist[s] = 0;
    ll di;

    __gnu_pbds::priority_queue<pair<ll, int>> q;
    vector<decltype(q)::point_iterator> its(N);
    q.push({0, s});

    auto relax = [&](int i, ll cap, ll cost, int dir) {
      ll val = di - pi[i] + cost;
      if (cap && val < dist[i]) {
        dist[i] = val;
        par[i] = {s, dir};
        if (its[i] == q.end())
          its[i] = q.push({-dist[i], i});
        else
          q.modify(its[i], {-dist[i], i});
      }
    };

    while (!q.empty()) {
      s = q.top().second;
      q.pop();
      seen[s] = 1;
      di = dist[s] + pi[s];
      trav(i, ed[s]) if (!seen[i])
        relax(i, cap[s][i] - flow[s][i], cost[s][i], 1);
      trav(i, red[s]) if (!seen[i]) relax(i, flow[i][s], -cost[i][s], 0);
    }
    rep(i, 0, N) pi[i] = min(pi[i] + dist[i], INF);
  }

  pair<ll, ll> maxflow(int s, int t) {
    ll totflow = 0, totcost = 0;
    while (path(s), seen[t]) {
      ll fl = INF;
      for (int p, r, x = t; tie(p, r) = par[x], x != s; x = p)
        fl = min(fl, r ? cap[p][x] - flow[p][x] : flow[x][p]);
      totflow += fl;
      for (int p, r, x = t; tie(p, r) = par[x], x != s; x = p)
        if (r)
          flow[p][x] += fl;
        else
          flow[x][p] -= fl;
    }
    rep(i, 0, N) rep(j, 0, N) totcost += cost[i][j] * flow[i][j];
    return {totflow, totcost};
  }
};



int main() {
  cin >> N >> M;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> G[i][j];
    }
  }
  int c = 0;
  map<int, int> matchIndex;
  for (int i = 0; i < M; i++) {
    cin >> P[i];
    matchIndex[P[i]] = c++;
  }
  for (int i = 0; i < M; i++) {
    cin >> F[i];
    matchIndex[F[i]] = c++;
  }
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
      }
    }
  }
  MCMF mcmf(c + 2);
  int src = c;
  int sink = c + 1;
  for (int i = 0; i < M; i++) {
    int cp = matchIndex[P[i]];
    for (int j = 0; j < M; j++) {
      int cf = matchIndex[F[j]];
      mcmf.addEdge(cp, cf, 1, G[P[i]][F[j]]);
    }
  }
  for (int i = 0; i < M; i++) {
    mcmf.addEdge(src, matchIndex[P[i]], 1, 0);
    mcmf.addEdge(matchIndex[F[i]], sink, 1, 0);
  }
  auto res = mcmf.maxflow(src, sink);
  assert(res.first == M);
  cout << res.second << endl;
  return 0;
}
