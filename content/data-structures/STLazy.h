/**
 * Author: Bomba de tenedores
 * Description: Segment tree Lazy data structure
 * All the ranges are [a,b)
 * Time: O(\log N) each function
 */
 
int N, A[MAXN];
struct STN{
    void merge(STN& L, STN& R) {}
    void operator=(ll a) {}
};

STN ST[4*MAXN];
ll lzy[4*MAXN];
void STB(int id = 1, int l = 0, int r = N){
    if(r - l < 2){
        ST[id] = A[l];
        return;
    }
    int m = (l+r)>>1, L = id<<1, R = L|1;
    STB(L, l, m); STB(R, m, r);
    ST[id].merge(ST[L], ST[R]);
}

// Update node and lazy
void upd(int id, int l, int r, ll x){
    lzy[id] += x;
    //ST[id].val += (r - l)*x;
}

// Propagate the update from lazy
void shift(int id, int l, int r){
    int m = (l+r)>>1, L = id<<1, R = L|1;
    upd(L, l, m, lzy[id]);
    upd(R, m, r, lzy[id]);
    lzy[id] = 0;
}

STN STQ(int x, int y, int id = 1, int l = 0, int r = N){
    if(x == l && y == r) return ST[id];
    shift(id, l, r);
    int m = (l+r)>>1, L = id<<1, R = L|1;
    if(x >= m) return STQ(x, y, R, m, r);
    if(y <= m) return STQ(x, y, L, l, m);
    STN res, ln = STQ(x, m, L, l, m), rn = STQ(m, y, R, m, r);
    return res.merge(ln, rn), res;
}

void STU(int x, int y, int v, int id = 1, int l = 0, int r = N){
    if(x >= r || y <= l) return;
    if(x <= l && y >= r) {
        upd(id, l, r, v);
        return;
    }
    shift(id, l, r);
    int m = (l+r)>>1, L = id<<1, R = L|1;
    STU(x, y, v, L, l, m);
    STU(x, y, v, R, m, r);
    ST[id].merge(ST[L], ST[R]);
}

