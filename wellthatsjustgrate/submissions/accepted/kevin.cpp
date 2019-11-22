// INCOMPLETE SOLUTION

#include <bits/stdc++.h>
using namespace std;

typedef double T;

template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    P operator+ (P p) const { return P(x + p.x, y + p.y); }
    P operator- (P p) const { return P(x - p.x, y - p.y); }
    P operator* (T d) const { return P(x * d, y * d); }
    T cross(P p) const { return x * p.x - y * p.y; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
};

template<class P> bool onSegment(P s, P e, P p) {
    return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}

template<class P> vector<P> segInter(P a, P b, P c, P d) {
    auto oa = c.cross(d, a), ob = c.cross(d, b);
         oc = a.cross(d, b), od = a.cross(b, d);
    if (sgn(oa) * sgn(ob) < 0 && sgn(oc) * sgn(od) < 0) {
        return {(a * ob - b * oa) / (ob - oa)};
    }
    set<P> s;
    return {all(s)};
}

template<class P>
bool inPolygon(vector<P> &p, P a, bool strict = true) {
    int cnt = 0, n = sz(p);
    rep(i, 0, n) {
        P q = p[(i + 1) % n];
        if (onSegment(p[i], q, a)) return !strict;
        cnt ^= ((a.y<p[i].y) - (a.y < q.y)) * a.cross(p[i], q) > 0;
    }
    return cnt;
}

int L, W, N, P;
vector<pair<P, P>> segments;

static inline void falls_through() {
    double x1, y1, x2, y2;
    scanf(" %lf %lf %lf %lf", &x1, &y1, &x2, &y2);

}

int main() {
    cin.sync_with_stdio(0); cin.tie(0);
    cin.exceptions(cin.failbit);
    
    scanf(" %d %d %d %d", &L , &W, &N, &P);
    for (int i = 0; i < N; ++i) {
        double x1, y1, x2, y2;
        scanf(" %lf %lf %lf %lf", &x1, &y1, &x2, &y2);
        segments.push_back(make_pair(P(x1, y1), P(x2, y2)));
    }
    
    for (int i = 0; i < P; ++i) {
        falls_through();
    }
}
