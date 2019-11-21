#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int MOD = 998244353;

ll mul(ll x,ll y){
	return (x * y) % MOD;
}

ll mod_pow(ll x, ll p){
	ll res = 1;
	while(p){
		if(p&1)res = mul(res,x);
		x = mul(x,x);
		p/=2;
	}
	return res;
}

int main(){
	int n;
	cin >> n;
	if(n&1){
		cout << 0 << '\n';
	}
	else{
		ll ans = mod_pow(n, 1LL * n/2 * (MOD - 2));
		for(int i = n;i > n/2; --i){
			ans = mul(ans, i);
		}
		if(n % 4 == 2)ans = MOD - ans;
		cout << ans << '\n';
	}
}
