#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int MAXLEN = 20;
const string pass = "Feline good!";
const string fail = "Get meowt!";

int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	int n,mnl,mxl;
	cin >> n >> mnl >> mxl;
	bool val[256][256] = {};
	for(int i = 0;i < 26;++i){
		int len;
		string s;
		cin >> len >> s;
		for(char c:s){
			val['a' + i][c] = 1;
		}
	}
	bool valstring[MAXLEN + 5][256] = {};
	vector<string> v(n);
	for(int i = 0;i < n; ++i){
		cin >> v[i];
		string &s = v[i];
		bool valid = true;
		for(int i = 0;i < (int)s.length() - 1; ++i){
			if(!val[s[i]][s[i+1]]){
				valid = false;	
				break;
			}
		}
		if(!valid)continue;
		else{
			valstring[s.length()][s[0]] = 1;
		}
	}


	for(int i = 0;i < n; ++i){
		string &s = v[i];
		int slen = s.length();
		bool valid = true;
		for(int i = 0;i < slen - 1; ++i){
			if(!val[s[i]][s[i+1]]){
				valid = false;	
				break;
			}
		}
		if(!valid || slen > mxl){
			cout << fail << '\n';
			continue;
		}
		else if(s.length() >= mnl && s.length() <= mxl){
			cout << pass << '\n';
			continue;
		}
		valid = false;
		char end = s[slen - 1];
		for(int len = max(mnl - slen,0); len + slen <= mxl; ++len){
			for(char nxt = 'a';nxt <= 'z'; ++nxt){
				if(val[end][nxt] && valstring[len][nxt]){
					valid = true;	
				}
			}
		}
		cout << (valid?pass:fail) << '\n';
	}
}
