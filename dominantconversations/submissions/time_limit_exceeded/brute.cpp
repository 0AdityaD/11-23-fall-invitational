#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#define ll long long
using namespace std;

const int N = 1000000 + 5;
int cnt[N] = {};
int a[N];
ll ans[N] = {};

int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	int n,k;
	cin >> n >> k;
	for(int i = 0;i < n; ++i){
		cin >> a[i];
	}
	for(int i = 0;i < n; ++i){
		memset(cnt,0,sizeof(cnt));	
		int best = -1, bestcnt = -1;
		for(int j = i; j < n; ++j){
			cnt[a[j]]++;
			if(cnt[a[j]] > bestcnt){
				bestcnt = cnt[a[j]];
				best = a[j];
			}
			if(bestcnt * 2 > (j - i + 1)){
				++ans[best];
			}
		}
	}
	for(int i= 0;i < k; ++i){
		cout << ans[i] << '\n';
	}
}
