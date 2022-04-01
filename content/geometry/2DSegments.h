/**
 * Author: Marcos Lerones
 * Description: 2D Segments useful functions
 */
bool inDisk(pt a, pt, b, pt p){
    return dot(a-p, b-p) <= 0;
}
bool onSegment(pt a, pt b, pt p){
    return orient(a,b,p) == 0 && inDisk(a,b,p);
}
bool properInter(pt a, pt b, pt c, pt d, pt &out){
    double oa = orient(c, d, a),
           ob = orient(c, d, b);
           oc = orient(a, b, c);
           od = orient(a, b, d);
    if(oa*ob < 0 && oc*od < 0){
        out = (a*ob - b*oa) / (ob - oa);
        return true;
    }
    return false;
}
struct cmpX{
    bool operator()(pt a, pt b){
        return mkt(a.x, a.y) < mkt(b.x, b.y);
    }
};
set <pt,cmpX> inters(pt a, pt b, pt c, pt d){
    pt out;
    if(properInter(a, b, c, d, out)) return {out};
    set<pt,cmpX> s;
    if(onSegment(c, d, a)) s.insert(a);
    if(onSegment(c, d, b)) s.insert(b);
    if(onSegment(a, b, c)) s.insert(c);
    if(onSegment(a, b, d)) s.insert(d);
    return s;
}
double segPoint(pt a, pt b, pt p){
    if(a != b){
        line l(a, b);
        if(l.cmpProj(a, p) && l.cmpProj(p, b))
            return l.dist(p);
    }
    return min( abs(p-a), abs(p-b) );
}
double segSeg(pt a, pt b, pt c, pt d){
    pt aux;
    if(properInter(a, b, c, d, aux)) return 0;
    return min({segPoint(a, b, c), segPoint(a, b, d),
                segPoint(c, d, a), segPoint(c, d, b)});
}
