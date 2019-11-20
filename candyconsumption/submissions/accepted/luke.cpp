#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MOD = 1e9  + 7;

ll add(ll x, ll y){
	return (x + y) % MOD;
}

ll mul(ll x, ll y){
	return (x * y) % MOD;
}

int main(){
	cin.tie(0);	
	cout.tie(0);	
	ios_base::sync_with_stdio(0);
	int n;
	cin >> n;
	ll ans = 0;
	ll choose = 1;
	for(int i = 1;i <= n; ++i){
		choose = mul(choose, n-i+1);
		ans = add(ans, mul(i,mul(i+1, choose)));	
	}
	cout << ans << '\n';
}
