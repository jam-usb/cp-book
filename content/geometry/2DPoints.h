/**
 * Author: Marcos Lerones
 * Description: 2D points useful functions
 */
typedef double T;
typedef complex<T> pt;
#define x real() // DO NOT USE x & y AS VARIABLE NAMES!!!
#define y imag()
#define mkt make_tuple
const double PI = 2*acos(0.0);


int sgn(T a) {return (a < 0) - (a > 0);}
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

// Orientation
bool isPerp(pt v, pt w) {return dot(v, w) == 0;}
double angle(pt v, pt w){ // Range [0, pi]
    double cosTh = dot(v,w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTh)));
}
// < 0 c is left of ab, > 0 c is right, = 0 colinear
T orient(pt a, pt b, pt c) {return cross(b-a,c-a);}
bool inAngle(pt a, pt b, pt c, pt p){ // P is in angle BAC
    assert(orient(a,b,c) != 0);
    if(orient(a,b,c) < 0) swap(b, c);
    return orient(a, b, p) >= p && orient(a, c, p) <= 0;
}
double orientAngle(pt a, pt b, pt c){
    return (orient(a,b,c) >= 0) ?
            angle(b-a,c-a) : 2*PI - angle(b-a,c-a);
}
bool isConvex(vector<pt> p){
    bool hasPos = 0, hasNeg = 0;
    int n = p.size();
    FOR(i,0,n){
        int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
        if(o > 0) hasPos = 1;
        if(o < 0) hasNeg = 1;
    }
    return !(hasPos && hasNeg);
}

// Polar Sort
bool half(pt p){
    assert(p.x != 0 || p.y != 0);
    return p.y > 0 || (p.y == 0 && p.x < 0);
}
void polarSort(vector<pt> &v) {
    sort(all(v), [](pt v, pt w) {
        return mkt(half(v), 0, sq(v)) <
               mkt(half(w), cross(v, w), sq(w));
    }
}
