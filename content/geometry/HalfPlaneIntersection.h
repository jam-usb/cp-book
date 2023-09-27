/**
 * Author: cp-algorithms
 * Description: Find the intersection of $n$ half planes which
 * is either emtpy, a convex polygon or infinite.
 * Time: $O(n\log{n})$
 */

 /*
  * Common problems:
  * - Convex polygon intersection: treat each side as a halfplane and intersect all
  * - Visibility on plane: find a point that can see all sides of a polygon, find a point 
  *   that can see a set of point in a specific order
  * - Check in BS: Usually problem needs to translate the halfplanes by some param and
  *   find if the intersection is empty. This works to find the biggest circumference that
  *   can be inscribed in a convex polygon
  * - 2D Linear Programming: find a solution to a set of inequations of the form Ax + By + C <= 0
  */
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