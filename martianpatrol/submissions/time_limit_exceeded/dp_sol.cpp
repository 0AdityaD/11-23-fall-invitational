#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD = 1e9 + 7;

ll add(ll x, ll y){
	return (x + y) % MOD;
}

int main(){
	int n,t;
	cin >> n >> t;
	int open = 0;
	for(int i = 1;i <= n; ++i){
		int x,y;
		cin >> x >> y;
		open += x == 0;
		open += y == 0;
	}
	++n;
	while(n > 10000); // otherwise rte
	ll dp[n+1][n+1] = {};
	dp[0][0] = 1;
	for(int i = 1;i <= n;++i){
		dp[i][0] = add(dp[i-1][0], dp[i-1][1]);
		for(int j = 1;j <= i; ++j){
			dp[i][j] = add(dp[i-1][j-1], add(dp[i-1][j], dp[i-1][j+1]));
		}
	}
	ll ans = dp[n][0];
	ans = (ans * open) % MOD;
	cout << ans << '\n';
}
