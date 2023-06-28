/**
 * Author: Marcos Lerones
 * Description: 2D Polygons useful functions
 */
double areaPoly(vector<pt> &p){
    double area = 0.0;
    int n = p.size();
    FOR(i,0,n)
        area += cross(p[i], p[(i+1)%n]);
    return abs(area) / 2.0;
}
bool above(pt a, pt p){
    return p.y >= a.y;
}
bool crossesRay(pt a, pt p, pt q){
    return (above(a,q) - above(a,p)) * (orient(a, p, q) > 0);
}
// if strict return 0 if a is on the boundary
bool inPoly(vector<pt> &p, pt a, bool strict = 1){
    int numCross = 0, n = p.size();
    FOR(i,0,n){
        if(onSegment(p[i], p[(i+1)%n], a))
            return !strict;
        numCross += crossesRay(a, p[i], p[(i+1)%n]);
    }
    return numCross & 1;
}
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