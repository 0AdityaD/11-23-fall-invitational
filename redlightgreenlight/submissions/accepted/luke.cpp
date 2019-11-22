#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<double,int> pdi;

struct edge{
	int to, len, g, r, ti;		
	double waittime(double cur){
		if(cur < ti)return ti - cur;

		cur-=ti;
		cur = fmod(cur, (g + r));
		if(cur < g)return 0;
		else return g + r - cur;
	}
};

const int N = 50000 + 5;

vector<edge> g[N];

int n,m,t;

bool dij(double speed){
	double d[N];
	fill(d, d+N, INT_MAX);
	priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
	pq.push({0,1});
	while(pq.size()){
		double ctime = pq.top().first; 	
		int cur = pq.top().second; 	
		pq.pop();
		if(ctime < d[cur]){
			d[cur] = ctime;
			for(edge &e: g[cur]){
				double wait = e.waittime(ctime);	
				double len = ((double)e.len)/speed;
				if(wait + len + ctime < d[e.to]){
					pq.push({wait + len + ctime, e.to});
				}
			}
		}
	}
	return d[n] < t;
}

const double EPS = 1e-8;

int main(){
	cin.tie(0);	
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	cin >> n >> m >> t;
	for(int i = 0;i < m; ++i){
		int u,v,l,gi,r,t;	
		cin >> u >> v >> l >> gi >> r >> t;
		g[u].push_back({v,l,gi,r,t});
	}
	double l = 0, r = 1e16;
	double ans = INT_MAX;
	while(l + EPS < r){
		double m = (r + l)/2;
		if(dij(m)){
			ans = m;
			r = m;				
		}
		else{
			l = m;	
		}
	}
	cout.precision(14);
	cout << ans << '\n';
}
