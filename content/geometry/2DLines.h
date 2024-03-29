/**
 * Author: Marcos Lerones
 * Description: 2D lines useful functions
 */
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

// Interior: bisector pointing between 2 directions
line bisector(line l1, line l2, bool interior){
    assert(cross(l1.v, l2.v) != 0);
    double sign = interior ? 1 : -1;
    return {l2.v/abs(l2.v) + l1.v/abs(l1.v) * sign,
            l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
}
