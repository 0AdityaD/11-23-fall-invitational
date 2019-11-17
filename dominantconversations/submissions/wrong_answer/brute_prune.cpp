#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	int n,k;
	cin >> n >> k;
	int cnt[k] = {};
	int a[n];
	for(int i = 0;i < n; ++i){
		cin >> a[i];
	}
	ll ans[k] = {};
	for(int i = 0;i < n; ++i){
		int best = -1, bestcnt = -1;
		int lst = n-1;
		for(int j = i; j < n; ++j){
			cnt[a[j]]++;
			if(cnt[a[j]] > bestcnt){
				bestcnt = cnt[a[j]];
				best = a[j];
			}
			if(bestcnt * 2 > (j - i + 1)){
				++ans[best];
			}
			else if(j-i >= 100){
				lst = j;	
				break;
			}
		}
		for(int j = i; j <= lst; ++j)--cnt[a[j]];
	}
	for(int i= 0;i < k; ++i){
		cout << ans[i] << '\n';
	}
}
