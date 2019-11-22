#include <bits/stdc++.h>
using namespace std;
const int N = 505;
const int inf = INT_MAX;
int d[N][N];

int main(){
	cin.tie(0);	
	cout.tie(0);	
	ios_base::sync_with_stdio(0);
	int n,m;
	cin >> n >> m;
	for(int i = 0; i < n; ++i){
		for(int j = 0;j < n; ++j){
			cin >> d[i][j];
		}
	}
	bool from[n] = {};
	bool to[n] = {};

	for(int i = 0;i < m; ++i){
		int x;
		cin >> x;
		from[x] = 1;
	}

	for(int i = 0;i < m; ++i){
		int x;
		cin >> x;
		to[x] = 1;
	}


	for(int k = 0;k < n; ++k)
		for(int i = 0;i < n; ++i)
			for(int j = 0;j < n; ++j)
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

	int ans = 0;
	for(int i = 0;i < n; ++i){
		if(from[i]){
			int best = inf, bestind = -1;
			for(int j = 0;j < n; ++j){
				if(to[j] && best > d[i][j]){
					best = d[i][j];
					bestind = j;
				}
			}
			to[bestind] = 0;
			ans += best;
		}
	}
	cout << ans << '\n';
}
