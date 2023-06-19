T cross(pt v, pt w) {return (conj(v)*w).y;}
T orient(pt a, pt b, pt c) {return cross(b-a, c-a);}
 
bool cmp(pt a, pt b) {
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}
 
T mDist (pt a, pt b) {
	return max(llabs(a.x - b.x), llabs(a.y - b.y));
}
 
vector <pt> convexHull (vector <pt> &P) {
	sort(all(P), cmp);
	vector <pt> UH;
	vector <pt> LH;
 
	for (auto p : P) {
		while (sz(UH) >= 2 && orient(UH[sz(UH)-2], UH.back(), p) >= 0) UH.pop_back();
		UH.pb(p);
	}
 
	reverse(all(P));
 
	for (auto p : P) {
		while (sz(LH) >= 2 && orient(LH[sz(LH)-2], LH.back(), p) >= 0) LH.pop_back();
		LH.pb(p);
	}
 
 
	for (auto p : LH) if (p != UH.back() and p != UH[0]) UH.pb(p);
	return UH;
}
