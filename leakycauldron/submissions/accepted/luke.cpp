#include <bits/stdc++.h>
using namespace std;
const int inf = 1000000;
const int N = 200 + 5;
int g[N+2][N+2];
int tp[N+2][N+2] = {};
bool val[N+2][N+2];
bool vis[N+2][N+2];

void dfs(int x, int y, int h){
	if(vis[x][y])return;
	vis[x][y] = 1;
	if(g[x][y] <= h){
		val[x][y] = 1;
		dfs(x+1,y,h);
		dfs(x-1,y,h);
		dfs(x,y+1,h);
		dfs(x,y-1,h);
	}
}

int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	int n,m,h;	
	cin >> n >> m >> h;
	for(int i = 0; i <= n + 1; ++i)
		for(int j = 0;j <= m + 1; ++j)
			g[i][j] = inf;

	for(int i = 1;i <= n; ++i){
		for(int j = 1;j <= m; ++j){
			cin >> g[i][j]; 
		}	
	}

	for(int hi = 0;hi <= h; ++hi){
		memset(val,0,sizeof(val));
		memset(vis,0,sizeof(vis));
		dfs(n/2+1,m/2+1,hi);	
		for(int i = 1;i <= n; ++i)
			for(int j = 1;j <= m; ++j){
				if(!val[i][j]){
					tp[i][j] = 0;	
				}
				else{
					tp[i][j] = val[i-1][j] ? tp[i-1][j] + 1 : 1 ; 
				}
				
			}

		stack<int> s;
		int ans = 0;
		for(int i = 1;i <= n; ++i){
			auto &hist = tp[i];
			int j = 1;
			while(j <= m){
				if(s.empty() || hist[j] >= hist[s.top()]){
					s.push(j);	
					++j;
				}
				else{
					int topv = s.top();
					s.pop();

					int area = hist[topv] * (s.empty() ? j - 1: j - s.top() - 1);
					ans = max(area, ans);

				}
			}
			while(s.size()){
				int topv = s.top();
				s.pop();
				
				int area = hist[topv] * (s.empty() ? m : m - s.top() - 1);
				ans = max(area, ans);

			}
		}
		cout << ans << '\n';
	}
}
