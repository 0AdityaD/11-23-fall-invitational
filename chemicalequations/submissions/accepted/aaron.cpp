#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

const ll INF = 1e18;
const int MOD = 1000000007;
const ld EPS = 1e-9;
const ld PI = acos(-1);

#define x first
#define y second

int N;
unordered_map<string, vector<pair<int, string>>> reactions;

map<string, map<string, int>> memo;
map<string, int> baseIngreds(string name) {
    if (memo.count(name)) return memo[name];
    map<string, int> res;
    if (!reactions.count(name)) res[name] = 1;
    else {
        for (auto p : reactions[name]) {
            map<string, int> rec = baseIngreds(p.second);
            for (auto x : rec)
                res[x.first] += x.second * p.first;
        }
    }
    return memo[name] = res;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(10);

    cin >> N;
    for (int i = 0; i < N; i++) {
        string name; int R; cin >> name >> R;
        vector<pair<int, string>> ingreds;
        for (int j = 0; j < R; j++) {
            int q; string b; cin >> q >> b;
            ingreds.push_back({q, b});
        }
        reactions[name] = ingreds;
    }

    string comp; cin >> comp;
    map<string, int> base = baseIngreds(comp);
    for (auto p : base)
        cout << p.first << " " << p.second << "\n";

    return 0;
}
