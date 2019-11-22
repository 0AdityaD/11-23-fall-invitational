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
#define pb push_back

struct MCMF{
    struct Edge{
        int destination, capacity, residualFlow, cost;
        Edge* counterEdge;
    };

    int N, distance [510], parents [510];
    Edge* parentEdge [510];
    vector<Edge*> *adjacency;

    void resetIt(){ adjacency = new vector<Edge*>[N]; }

    void addEdge(int source, int destination, int capacity, int cost){
        Edge* e1 = new Edge;
        e1->destination = destination; e1->capacity = capacity;
        e1->residualFlow = capacity; e1->cost = cost;
        Edge* e2 = new Edge;
        e2->destination = source; e2->capacity = capacity;
        e2->residualFlow = 0; e2->cost = -cost;
        e1->counterEdge = e2; e2->counterEdge = e1;
        adjacency[source].pb(e1); adjacency[destination].pb(e2);
    }

    bool searchIt(int source, int sink){
        for(int i = 0; i < N; i++){
            parents[i] = -1;
            distance[i] = MOD;
        }
        distance[source] = 0;
        bool updated = true;
        set<int> active; active.insert(source);
        for(int i = 0; i < N-1 && updated; i++){
            updated = false;
            set<int> newActive;
            for(int u : active)
                for(int e = 0; e < adjacency[u].size(); e++){
                    if(adjacency[u][e]->residualFlow > 0){
                        int v = adjacency[u][e]->destination;
                        int w = adjacency[u][e]->cost;
                        if(distance[v] > distance[u]+w){
                            distance[v] = distance[u]+w;
                            parents[v] = u;
                            parentEdge[v] = adjacency[u][e];
                            newActive.insert(u); newActive.insert(v);
                            updated = true;
                        }
                    }
                }
            active = newActive;
        }
        return parents[sink] != -1;
    }

    int calcIt(int s, int t, int requiredFlow){
        int u, v, currFlow = 0, runningCost = 0;
        Edge *te1, *te2;
        while(searchIt(s, t)){
            int path_flow = MOD;
            for(v = t; v != s; v = parents[v]){
                u = parents[v];
                te1 = parentEdge[v];
                path_flow = min(path_flow, te1->residualFlow);
            }
            path_flow = min(path_flow, requiredFlow-currFlow);
            for(v = t; v != s; v = parents[v]){
                u = parents[v];
                te1 = parentEdge[v];
                te2 = te1->counterEdge;
                te1->residualFlow -= path_flow;
                te2->residualFlow += path_flow;
                runningCost += path_flow*(te1->cost);
            }
            currFlow += path_flow;
            if(currFlow == requiredFlow) break;
        }
        if(currFlow == requiredFlow) return runningCost;
        else return MOD;
    }
};

int N, M, dist[500][500], P[500], F[500];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(10);

    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> dist[i][j];

    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    MCMF flow;
    flow.N = 510;
    flow.resetIt();

    int src = 500, sink = 501;
    for (int i = 0; i < M; i++) {
        int p; cin >> p;
        P[p]++;
    }
    for (int i = 0; i < M; i++) {
        int f; cin >> f;
        F[f]++;
    }
    for (int i = 0; i < N; i++)
        flow.addEdge(src, i, P[i], 0);
    for (int i = 0; i < N; i++)
        flow.addEdge(i, sink, F[i], 0);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (P[i] && F[j])
                flow.addEdge(i, j, min(P[i], F[j]), dist[i][j]);
    
    long long res = flow.calcIt(src, sink, M);
    cout << res << "\n";

    return 0;
}
