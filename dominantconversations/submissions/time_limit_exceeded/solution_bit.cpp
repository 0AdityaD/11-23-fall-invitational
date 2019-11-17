#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#define ll long long
using namespace std;

const int N = 1000000 + 5;
const int L = 0;
const int R = 2*N;
const ll mx = 4 * 2 * N;

// todo -> replace int with LONG LONG
struct tree{
	ll ts[4 * 2 * N] = {};
	ll is[4 * 2 * N] = {};
	ll d[4  * 2 * N] = {};
	int clear[4 * 2 * N] = {};

	tree(){
		memset(ts,0,sizeof(ts));
		memset(is,0,sizeof(is));
		memset(d,0,sizeof(d));
		memset(clear,0,sizeof(clear));
	}

	// x1 + x2 + x3 + ...  
	ll query1(int l, int r, int l0, int r0, int ind){
		if(l0 >= r0)return 0;
		if(r <= l0 || r0 <= l)return 0;
		assert(ind < mx);
		if(l <= l0 && r0 <= r)return ts[ind]; 
		push(l,r,l0,r0,ind);
		int mid = (l0 + r0)/2;
		return query1(l, r, l0, mid, 2*ind) + query1(l, r, mid, r0, 2*ind + 1);
	}

	ll query2(int l, int r, int l0, int r0, int ind){
		if(l0 >= r0)return 0;
		if(r <= l0 || r0 <= l)return 0;
		assert(ind < mx);
		if(l <= l0 && r0 <= r)return is[ind]; 
		push(l,r,l0,r0,ind);
		int mid = (l0 + r0)/2;
		return query2(l, r, l0, mid, 2*ind) + query2(l, r, mid, r0, 2*ind + 1);
	}

	void reset(int l, int r, int l0, int r0, int ind){
		if(l0 >= r0)return;
		if(r <= l0 || r0 <= l)return;	
		//cout << l0 << " " << r0 << " " << ind << endl; 
		//cout << r0 - l0 << ' ' << ind << endl;
		assert(ind < mx);
		if(l <= l0 && r0 <= r){
			clear[ind] = 1;
			ts[ind] = 0;
			is[ind] = 0;
			d[ind] = 0;
		}
		else{
			push(l,r,l0,r0,ind);
			int mid = (l0 + r0)/2;
			reset(l,r,l0,mid,2*ind);
			reset(l,r,mid,r0,2*ind+1);
			assert(ind < mx/2);
			ts[ind] = ts[2*ind] + ts[2*ind+1];	
			is[ind] = is[2*ind] + is[2*ind+1];	
		}
	}

	void inc(int l, int r, int l0, int r0, int ind, ll val){
		if(l0 >= r0)return;
		if(r <= l0 || r0 <= l)return; // nothing
		assert(ind < mx);
		assert(val != 0);
		if(l <= l0 && r0 <= r){
			d[ind] += val; 
			ts[ind] += val * (r0 - l0);
			is[ind] += val * (2*N - l0 + 2*N - (r0 - 1)) * (r0 - l0)/2;
		}
		else{
			push(l,r,l0,r0,ind);
			int mid = (l0 + r0)/2;
			inc(l,r,l0,mid,2*ind,val);
			inc(l,r,mid,r0,2*ind+1,val);
			ts[ind] = ts[2*ind] + ts[2*ind+1];
			is[ind] = is[2*ind] + is[2*ind+1];
		}
	}

	void push(int l, int r, int l0, int r0, int ind){
		if(r0 - l0 <= 1)return;
		assert(ind < mx);
		int mid = (l0 + r0)/2;
		if(clear[ind] != 0){
			reset(l0,mid,l0,mid,2*ind);
			reset(mid,r0,mid,r0,2*ind+1);
			clear[ind] = 0;
		}
		if(d[ind] != 0){
			inc(l0,mid,l0,mid,2*ind,d[ind]);
			inc(mid,r0,mid,r0,2*ind+1,d[ind]);
			d[ind] = 0;
		}
	}
} t;


void clear(int l, int r){
	l += N;
	r += N;
	t.reset(l,r,L,R,1);
}

void inc(int l,int r){
	l += N;
	r += N;
	t.inc(l,r,L,R,1,1);
}

// [l, r)
int get_sum(int l, int r){
	l += N;		
	r += N;		
	return t.query1(l,r,L,R,1);
}

ll get_count(int l, int r){
	l += N;	
	r += N;	
	ll res = t.query2(l,r,L,R,1);
	res -= (2*N - r) * t.query1(l,r,L,R,1);
	return res;
}

int T[2*N];

void inc(int x){
	for(x+=N;x < 2*N;x += (x & -x)){
		++T[x];
	}
}

int query(int x){
	int res = 0;
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
	int a[n];
	vector<int> pa[k];
	for(int i = 0;i < n; ++i){
		cin >> a[i];
		pa[a[i]].push_back(i);
	}
	for(int i = 0;i < k;++i)pa[i].push_back(n);
	ll ans[k] = {};
	for(int i = 0;i < k; ++i){
		if(pa[i].size() <= 1000){
			clear(-N,N);
			int cursum = 0;
			int prior = -1;
			//inc(0,1);
			for(int j = 0;j < pa[i].size()-1; ++j){
				int len = pa[i][j] - prior - 1; 
				assert(len >= 0);
				inc(cursum - len,cursum + 1);
				cursum -= len;
				++cursum;
				ll mx = cursum - 1;
				ll left = pa[i][j+1] - pa[i][j];
				ans[i] += get_count(mx+1-left,mx+1) + left * get_sum(-N, mx+1-left); 
				// add this one
				//inc(cursum,cursum+1);
				prior = pa[i][j];
			}
		}
		else{
			memset(T,0,sizeof(T));
			int cursum = 0;		
			inc(0);
			for(int j = 0;j < n;++j){
				cursum += (a[j] == i ? 1 : -1);
				ans[i] += query(cursum - 1);
				inc(cursum);
			}
		}
	}
	for(int i = 0;i < k; ++i){
		cout << ans[i] << '\n';
	}
}
