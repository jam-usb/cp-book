// https://codeforces.com/group/3qadGzUdR4/contest/101706/problem/H
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int das;
#define FOR(i,n,m) for(int i = n; i < (int)m; i++)
#define ROF(i,n,m) for(int i = n; i > (int)m; i--)
#define ms(obj,val) memset(obj,val,sizeof(obj))
#define ri(a) das=scanf("%d", &a)
#define rii(a,b) ri(a), ri(b)
#define lri(a) das=scanf("%lld", &a)
#define lrii(a,b) lri(a), lri(b)
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x).size()
#define pb push_back
#define S second
#define F first

const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MOD = 1e9+7;
const int MAXN = 2e5+5;

void fastIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}


typedef long long T;
typedef complex<T> pt;
#define x real() // DO NOT USE x & y AS VARIABLE NAMES!!!
#define y imag()
#define mkt make_tuple
const double PI = 2*acos(0.0);

// > 0 c is left of ab, < 0 c is right, = 0 colinear
T cross(pt v, pt w) {return (conj(v)*w).y;}	
T orient(pt a, pt b, pt c) {return cross(b-a,c-a);}

int N, M, K;
vector<pt> P;

// triangle should be in clockwise order
bool inTriangle(const vector<pt> &tri, const pt p) {
	assert(sz(tri) == 3);
	return orient(tri[0], tri[1], p) <= 0 && orient(tri[1], tri[2], p) <= 0 && orient(tri[2], tri[0], p) <= 0;  
}

// poly should be in clockwise order
bool inConvexPoly(const vector<pt> &poly, const pt p) {
	assert(sz(poly) >= 3);
	int lo = 1, hi = sz(poly) - 2;
	while(lo < hi) {
		int mi = lo + (hi - lo + 1) / 2;
		if (orient(poly[0], poly[mi], p) <= 0)
			lo = mi;
		else
			hi = mi-1; 
	}
	return inTriangle({poly[0], poly[lo], poly[lo+1]}, p);
}


int main(){
	rii(N, M), ri(K);
	FOR(i,0,N) {
		int a,b; rii(a,b);
		P.pb(pt(a,b));
	}
	reverse(all(P));
	while(M--) {
		int a,b; rii(a,b);
		pt p(a,b);
		if (inConvexPoly(P, p)) --K;
	}
	if (K <= 0) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
