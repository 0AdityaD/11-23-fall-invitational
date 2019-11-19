#include <bits/stdc++.h>
using namespace std;
bool val[256][256];

bool is_valid(const string & s){
	for(int i = 0;i < s.length() - 1;++i){
		if(!val[s[i]][s[i+1]]){
			return false;
		}
	}
	return true;
}

const string fail = "Get meowt!";
const string pass = "Feline good!";

int main(){
	cin.tie(0);
	cout.tie(0);
	ios_base::sync_with_stdio(0);
	int n,minlen,maxlen;
	cin >> n >> minlen >> maxlen;
	for(char c = 'a'; c <= 'z'; ++c){
		int len;
		string s;
		cin >> len >> s;
		for(char t: s){
			val[c][t] = 1;
		}
	}
	
	vector<string> v[128];
	vector<string> in(n);
	for(int i = 0;i < n; ++i){
		string s;
		cin >> s;
		if(is_valid(s))v[s[0]].push_back(s);
		in[i] = s;
	}

	for(int i = 0;i < n; ++i){
		string &s = in[i];
		if(!is_valid(s)){
			cout << fail << '\n';
			continue;
		}
		if(minlen <= s.length() && s.length() <= maxlen){
			cout << pass << '\n';
			continue;
		}

		char end = s[s.length() - 1];
		bool valid = false;
		for(char c = 'a';c <= 'z'; ++c){
			if(val[end][c]){
				for(int i = 0;i < v[c].size(); ++i){
					int len = s.length() + v[c][i].length();
					if(minlen <= len && len <= maxlen){
						valid = true;
						break;
					}
				}
			}
			if(valid)break;
		}
		cout << (valid?pass:fail) << '\n';
	}
}
