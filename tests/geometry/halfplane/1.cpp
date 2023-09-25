// https://www.codechef.com/problems/CHN02

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
#define ms(obj,val) memset(obj,val,sizeof(obj))
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
#define mkt make_tuple

const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MOD = 1e9+7;
const int MAXN = 2e5+5;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

void fastIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}

int sgn(T a) {return (a > 0) - (a < 0);}
T sq(pt p) {return p.x*p.x + p.y*p.y;}
double abs(pt p) {return sqrt(sq(p));}

// Transformations
pt translate(pt v, pt p) {return p+v;} //Move p through v
pt scale(pt c, double fact, pt p) {return c + (p - c)*fact;}
pt rot(pt p, double a) {return p * polar(1.0, a);}
pt perp(pt p) {return {-p.y, p.x};}

// Arbitrary linear Transformation f given f(p) and f(q)
pt linearTransfo(pt p, pt q, pt r, pt fp, pt fq){
    return fp + (r-p) * (fq-fp) / (q-p);
}

// Products
T dot(pt v, pt w) {return (conj(v)*w).x;}
T cross(pt v, pt w) {return (conj(v)*w).y;}

int half(pt p) { return p.y != 0 ? sgn(p.y) : -sgn(p.x); }
bool angleCmp(pt v, pt w) {
    return mkt(half(v), 0, sq(v)) <
           mkt(half(w), cross(v, w), sq(w));
}

struct line {
    pt v; T c;
    // Direction v, Offset c
    line(pt v, T c) : v(v), c(c) {}
    // Eq ax + by = c
    line(T a, T b, T c) : v(b, -a), c(c) {}
    // Points p and q
    line(pt p, pt q) : v(q-p), c(cross(v,p)) {}
    // < 0 right, = 0 inline, > 0 left
    T side(pt p) {return cross(v, p) - c;}
    double dist(pt p) {return abs(side(p)) / abs(v);}
    double sqDist(pt p) {return side(p)*side(p) / (double)sq(v);}
    line perpThrough(pt p) {return {p, p + perp(v)};}
    bool cmpProj(pt p, pt q) {return dot(v,p) < dot(v,q);}
    line translate(pt t) {return {v, c + cross(v, t)};}
    line shiftLeft(double d) {return {v, c + d*abs(v)};}
    pt proj(pt p) {return p - perp(v) * side(p) / sq(v);}
    pt refl(pt p) {return p - perp(v) * (T) 2 * side(p) / sq(v);}
};

bool inter(line l1, line l2, pt &out){
    T d = cross(l1.v, l2.v);
    if(d == 0) return false;
    out = (l2.v*l1.c - l1.v*l2.c) / d;
    return true;
}

const T eps = 1e-9, inf = 1e9;

struct Halfplane : public line {
    using line::line;
    bool out(pt p) { return side(p) < -eps; }
    bool operator<(const Halfplane &b) const { 
        return angleCmp(v, b.v); 
    }
};

pt isect(Halfplane &a, Halfplane &b) {
    pt p; assert(inter(a, b, p)); // No parallel lines
    return p;
}

vector<pt> halfplaneInters(vector<Halfplane> hplanes) {
    vector<pt> box = { // bounding box
        {inf, inf}, {-inf, inf}, 
        {-inf, -inf}, {inf, -inf}
    };
    FOR(i,0,4) hplanes.pb(Halfplane(box[i], box[(i+1)%4]));

    sort(all(hplanes));
    { // remove parallel planes
        vector<Halfplane> nps;
        for (auto hp : hplanes) {
            if (!sz(nps) || cross(nps.back().v, hp.v) > eps) {
                nps.pb(hp); continue;
            }

            if (hp.out(nps.back().proj({0,0}))) nps.back()=hp;
        }
        swap(hplanes, nps);
    }

    deque<Halfplane> poly;
    for (auto hp : hplanes) {
        while (sz(poly) > 1 && hp.out(isect(poly.back(), poly[sz(poly)-2]))) poly.pop_back();
        while (sz(poly) > 1 && hp.out(isect(poly[0], poly[1]))) poly.pop_front();

        if (sz(poly) && fabsl(cross(hp.v,poly.back().v)) < eps) 
            return {};

        poly.pb(hp);
    }

    while (sz(poly) > 2 && poly[0].out(isect(poly.back(), poly[sz(poly)-2]))) poly.pop_back();
    while (sz(poly) > 2 && poly.back().out(isect(poly[0], poly[1]))) poly.pop_front();

    if (sz(poly) < 3) return {};

    vector<pt> ret; // CAN HAVE REPEATED POINTS!!!
    FOR(i,0,sz(poly)) {
        int j = (i+1) % sz(poly);
        ret.pb(isect(poly[i], poly[j]));
    }

    return ret; 
}

double areaPoly(vector<pt> &p){
    double area = 0.0;
    int n = p.size();
    FOR(i,0,n)
        area += cross(p[i], p[(i+1)%n]);
    return abs(area) / 2.0;
}

void addPoly(vector<pt> &poly, vector<Halfplane> &hplanes) {
    FOR(i,0,sz(poly)) {
        int j = (i+1) % sz(poly);
        hplanes.pb(Halfplane(poly[i], poly[j]));
    }
}

int main(){

    vector<Halfplane> hplanes;

    int n; ri(n);
    FOR(i,0,n) {
        int c;
        vector<pt> poly;

        ri(c);
        FOR(j,0,c) { int xx, yy; rii(xx,yy); poly.pb({1.0*xx, 1.0*yy}); }
        addPoly(poly, hplanes);
    }

    auto sol = halfplaneInters(hplanes);
    printf("%.11lf\n", areaPoly(sol));
    
	return 0;
}
