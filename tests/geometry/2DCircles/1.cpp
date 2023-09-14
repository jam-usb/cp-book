// https://codeforces.com/gym/101208/attachments j

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef double T;
typedef complex<T> pt;

#define FOR(i,n,m) for(int i = n; i < (int)m; i++)
#define ROF(i,n,m) for(int i = n; i > (int)m; i--)
#define ms(obj,val) memset(obj, val, sizeof(obj))
#define ri(a) scanf("%d", &a)
#define rii(a,b) ri(a), ri(b)
#define lri(a) scanf("%lld", &a)
#define lrii(a,b) lri(a), lri(b)
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x).size()
#define pb push_back
#define S second
#define F first
#define x real()
#define y imag()

const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MOD = 1e9+7;
const int MAXN = 2e5+5;

void fastIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}

int sgn(T a) {return (a > 0) - (a < 0);}
T sq(pt v) { return v.x*v.x + v.y*v.y; }
double abs(pt v) {return sqrt(sq(v));}

pt perp(pt p) {return {-p.y, p.x};}
T dot(pt v, pt w) {return (conj(v)*w).x;}
T cross(pt v, pt w) {return (conj(v)*w).y;}

struct line {
	pt v; T c;
	line(pt p, pt q) : v(q-p), c(cross(v, p)) {}
	pt proj(pt p) { return p - perp(v) * side(p) / sq(v); }
	T side(pt p) {return cross(v, p) - c;}
	double sqDist(pt p) {return side(p)*side(p) / (double) sq(v);}
	bool cmpProj(pt p, pt q) {return dot(v, p) < dot(v, q); }
};

double angle(pt v, pt w) {
	double cosTh = dot(v, w) / abs(v) / abs(w);
	return acos(max(-1.0, min(1.0, cosTh)));
}

int circleLine(pt o, double r, line l, pair<pt,pt> &out) {
    double h2 = r*r - l.sqDist(o);
    if (h2 >= 0) { 
        pt p = l.proj(o);
        pt h = l.v*sqrt(h2)/abs(l.v); 
        out = {p-h, p+h};
    }
    return 1 + sgn(h2);
}

int n, r;
pt P[123];

double areaSlice(pt v, pt w) {
	return sgn(cross(v, w)) * r * r * angle(v, w);
}
double areaTri(pt v, pt w) {
	return cross(v, w);
}

int main() {
	rii(n, r);

	FOR(i,0,n) {
		int xx, yy;
		rii(xx, yy);
		P[i] = {1.0*xx, 1.0*yy};
	}

	pt o = {0.0, 0.0};


	double area = 0;
	FOR(i,0,n) {
		int j = (i+1) % n;

		pair<pt, pt> out;
		line l(P[i], P[j]);
		int ans = circleLine(o, r, l, out);

		if (ans == 0 || l.cmpProj(out.S, P[i]) || l.cmpProj(P[j], out.F)) {
			area += areaSlice(P[i], P[j]);
		}
		else {
			if (l.cmpProj(P[i], out.F) && l.cmpProj(out.S, P[j])) {
				area += areaSlice(P[i], out.F);
				area += areaTri(out.F, out.S);
				area += areaSlice(out.S, P[j]);
			}
			else if (l.cmpProj(P[i], out.F)) {
				area += areaSlice(P[i], out.F);
				area += areaTri(out.F, P[j]);
			}
			else if (l.cmpProj(out.S, P[j])) {
				area += areaTri(P[i], out.S);
				area += areaSlice(out.S, P[j]);
			}
			else {
				area += areaTri(P[i], P[j]);
			}
		}

	}

	printf("%.11lf\n", sgn(area) * area / 2.0);



	return 0;
}