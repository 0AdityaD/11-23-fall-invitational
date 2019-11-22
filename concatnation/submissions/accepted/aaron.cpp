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

int N, X, Y, succ[26][26], valid[100010];
string ids[100010];
set<int> len[26];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(10);

    cin >> N >> X >> Y;
    for (int i = 0; i < 26; i++) {
        int x; string t;
        cin >> x >> t;
        for (char c : t) succ[i][c-'a'] = 1;
    }

    for (int i = 0; i < N; i++) {
        string id; cin >> id;
        ids[i] = id;
        bool works = true;
        for (int j = 0; j + 1 < id.size(); j++)
            if (!succ[id[j]-'a'][id[j + 1]-'a']) works = false;
        valid[i] = works;
        if (id.size() && valid[i])
            len[id[0]-'a'].insert(id.size());
    }
    
    for (int i = 0; i < N; i++) {
        string id = ids[i];
        bool works = false;
        if (valid[i]) {
            vector<int> app;
            for (int j = 0; j < 26; j++) {
                if (!id.size()) app.push_back(j);
                else if (succ[id[id.size() - 1]-'a'][j]) app.push_back(j);
            }
            
            if (id.size() >= X && id.size() <= Y) works = true;
            else if (id.size() < X) {
                for (int j : app) {
                    int need = X - id.size();
                    auto it = len[j].lower_bound(need);
                    if (it != len[j].end()) {
                        int l = id.size() + *it;
                        if (l >= X && l <= Y) works = true;
                    }
                }
            }
        }
        if (works) cout << "Feline good!\n";
        else cout << "Get meowt!\n";
    }

    return 0;
}
