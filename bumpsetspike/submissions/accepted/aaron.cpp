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

char check() {
    int teamCnt = 1, lastP;
    char lastT, lastG;
    cin >> lastT >> lastP >> lastG;
    int wcnt = lastG == 'W', mcnt = lastG == 'M';
    for (int i = 1; i <= N; i++) {
        char t, g; int p;
        if (i != N) cin >> t >> p >> g;
        if (i == N || t != lastT) {
            if ((!wcnt || !mcnt) && teamCnt >= 2) return lastT;
            teamCnt = wcnt = mcnt = 0;
        }
        if (i != N) {
            teamCnt++;
            wcnt += g == 'W';
            mcnt += g == 'M';
            if (teamCnt > 3) return t;
            if (p == lastP && t == lastT) return t;
            lastT = t, lastP = p, lastG = g;
        }
    }
    return ' ';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(10);

    cin >> N;
    
    char res = check();
    if (res != 'A' && res != 'B') cout << "No violation\n";
    else cout << res << "\n";
    
    return 0;
}
