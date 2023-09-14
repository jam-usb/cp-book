/**
 * Author: Marcos Lerones
 * Description: 2D Circlues useful functions
*/

pt circumCenter(pt a, pt b, pt c) {
    b = b-a, c = c-a;
    assert(cross(b,c) != 0); 
    return a + perp(b*sq(c) - c*sq(b))/cross(b,c)/2;
}

int circleLine(pt o, double r, line l, pair<pt,pt> &out) {
    double h2 = r*r - l.sqDist(o);
    if (h2 >= 0) { 
        pt p = l.proj(o);
        pt h = l.v*sqrt(h2)/abs(l.v); 
        length h
        out = {p-h, p+h};
    }
    return 1 + sgn(h2);
}

int circleCircle(pt o1, double r1, pt o2, double r2, pair<pt,pt> &out) {
    pt d=o2-o1; double d2=sq(d);
    if (d2 == 0) {assert(r1 != r2); return 0;} 
    double pd = (d2 + r1*r1 - r2*r2)/2; 
    double h2 = r1*r1 - pd*pd/d2;
    if (h2 >= 0) {
        pt p = o1 + d*pd/d2, h = perp(d)*sqrt(h2/d2);
        out = {p-h, p+h};
    }
    return 1 + sgn(h2);
}

int tangents(pt o1, double r1, pt o2, double r2, bool inner, vector<pair<pt,pt>> &out) {
    if (inner) r2 = -r2;
    pt d = o2-o1;
    double dr = r1-r2, d2 = sq(d), h2 = d2-dr*dr;
    if (d2 == 0 || h2 < 0) {assert(h2 != 0); return 0;}
    for (double sign : {-1,1}) {
        pt v = (d*dr + perp(d)*sqrt(h2)*sign)/d2;
        out.push_back({o1 + v*r1, o2 + v*r2});
    }
    return 1 + (h2 > 0);
}

