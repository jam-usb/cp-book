/**
 * Author: Bomba de tenedores
 * Description: Persistent segment tree data structure implemented with
 * pointers
 * All the ranges are [a,b)
 * Time: O(\log N) each function
 */

struct STN{
    STN *l, *r;
    int val;
    STN(int val) : l(0), r(0), val(val) {}
    STN(STN *l, STN *r) : l(l), r(r), val(0){
        if(l) val += l->val;
        if(r) val += r->val;
    }
};

int N, A[MAXN];

STN* STB(int l = 0, int r = N){
    if(r - l < 2) return new STN(A[l]);
    int m = (l+r)>>1;
    return new STN(STB(l, m), STB(m, r));
}
int STQ(int x, int y, STN* v, int l = 0, int r = N){
    if(l >= r || x >= y) return 0;
    if(x == l && y == r) return v->val;
    int m = (l+r)>>1;
    return STQ(x, min(y, m), v->l, l, m)
         + STQ(max(x, m), y, v->r, m, r);
}
STN* STU(int p, int x, STN *v, int l = 0, int r = N){
    if(r - l < 2) return new STN(x);
    int m = (l+r)>>1;
    if(p < m)
        return new STN(STU(p, x, v->l, l, m), v->r);
    else
        return new STN(v->l, STU(p, x, v->r, m, r));
}
