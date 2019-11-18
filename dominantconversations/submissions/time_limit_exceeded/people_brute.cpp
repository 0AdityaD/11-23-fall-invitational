#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#define ll long long
using namespace std;

const int N = 1000000 + 5;
int a[N];
ll ans[N] = {};

ll T[2*N];

void inc(int x){
	for(x+=N;x < 2*N;x += (x & -x)){
		++T[x];
	}
}

ll query(int x){
	ll res = 0;
	for(x+=N;x;x &= x-1){
		res += T[x];	
	}
	return res;
}

int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	int n,k;
	cin >> n >> k;
	for(int i = 0;i < n; ++i){
		cin >> a[i];
	}
	for(int i = 0;i < k; ++i){
		memset(T,0,sizeof(T));
			int cursum = 0;		
			inc(0);
			for(int j = 0;j < n;++j){
				cursum += (a[j] == i ? 1 : -1);
				ans[i] += query(cursum - 1);
				inc(cursum);
			}	
	}
	for(int i= 0;i < k; ++i){
		cout << ans[i] << '\n';
	}
}
