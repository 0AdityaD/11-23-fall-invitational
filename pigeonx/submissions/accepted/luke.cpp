#include <bits/stdc++.h>
using namespace std;
const int N = 505;
const int INF = 20000000;
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
	int from[m] = {};
	int to[m] = {};

	for(int i = 0;i < m; ++i){
		cin >> from[i];
	}

	for(int i = 0;i < m; ++i){
		cin >> to[i];
	}

	for(int k = 0;k < n; ++k)
		for(int i = 0;i < n; ++i)
			for(int j = 0;j < n; ++j)
			{
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}


	int a[m+1][m+1] = {};
	for(int i = 0;i < m; ++i)
		for(int j = 0;j < m; ++j)
			a[i+1][j+1] = d[from[i]][to[j]];


	vector<int> u (m+1), v (m+1), p (m+1), way (m+1);
	for (int i=1; i<=m; ++i) {
		p[0] = i;
		int j0 = 0;
		vector<int> minv (m+1, INF);
		vector<bool> used (m+1, false);
		do {
			used[j0] = true;
			int i0 = p[j0],  delta = INF,  j1 = 0;
			for (int j=1; j<=m; ++j){
				if (!used[j]) {
					int cur = a[i0][j]-u[i0]-v[j];
					if (cur < minv[j])
						minv[j] = cur,  way[j] = j0;
					if (minv[j] < delta)
						delta = minv[j],  j1 = j;
				}
			}
			for (int j=0; j<=m; ++j){
				if (used[j]){
					
					u[p[j]] += delta;
					v[j] -= delta;
				}
				else
					minv[j] -= delta;
			}
			j0 = j1;
		} while (p[j0] != 0);
		do {
			int j1 = way[j0];
			p[j0] = p[j1];
			j0 = j1;
		} while (j0);
	}
	cout << -v[0] << '\n';
}
