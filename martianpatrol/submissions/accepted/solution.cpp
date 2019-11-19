#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MOD = 1000000007;

ll mul(ll x, ll y){
	return x * y % MOD;	
}

ll mpow(ll x, ll p){
	ll res = 1;
	while(p){
		if(p&1)res = mul(res,x);
		p>>=1;
		x = mul(x,x);
	}
	return res;
}

ll add(ll x, ll y){
	return (x + y) % MOD;
}

ll inverse(ll x){
	return mpow(x, MOD - 2);	
}

const int N = 1e6 + 5;

ll fac[N], inv[N];

ll comb(ll n, ll k){
	return mul(mul(fac[n], inv[k]), inv[n-k]);
}

ll cat(ll n){
	return mul(comb(2*n, n),inverse(n + 1));
}

int main(){
	fac[0] = inv[0] = 1;
	for(int i = 1;i < N; ++i){
		fac[i] = mul(fac[i-1], i); 
		inv[i] = inverse(fac[i]);
		assert(mul(fac[i],inv[i]) == 1);
	}

	int n;
	cin >> n;
	int open = 0;
	for(int i = 1;i <= n; ++i){
		int x, y;		
		cin >> x >> y;
		open += x == 0;
		open += y == 0;
	}
	ll ans = 0;
	++n;
	for(int i = 0; 2 * i <= n; ++i){
		ans = add(ans, mul(cat(i), comb(n, 2*i)));
	}
	ans = mul(ans, open);
	cout << ans << '\n';
}
