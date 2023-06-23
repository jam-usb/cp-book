// https://codeforces.com/gym/103577/problem/G
// this one also uses the subtree queries

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 LL;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

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


const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MOD = 1e9+7;
const int MAXN = 3e5+5;


void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}


int N;
vi G[MAXN];
int A[MAXN];

int T; // Timer
int IN[MAXN], OUT[MAXN], NXT[MAXN], SZ[MAXN], F[MAXN], H[MAXN];
void dfsSz(int v = 0, int p = -1) {
    SZ[v] = 1;
    if (p != -1) H[v] = H[p] + 1;
    for (auto &u : G[v]) if (u != p) {
            dfsSz(u, v);
            SZ[v] += SZ[u];
            if (SZ[u] > SZ[G[v][0]]) swap(u, G[v][0]);
        }
}
void dfsHLD(int v = 0, int p = -1) {
    IN[v] = T++;
    F[v] = p;
    A[IN[v]] = H[v];
    for (auto u : G[v]) if (u != p) {
            NXT[u] = (u == G[v][0] ? NXT[v] : u);
            dfsHLD(u, v);
        }
    OUT[v] = T;
}

// Todos los rangos son semi-abiertos [a,b)
struct STN {
    LL height_cnt = 0;
    LL sm = 0;
    void merge(STN& L, STN& R) {
        height_cnt = L.height_cnt + R.height_cnt;
        sm = L.sm + R.sm;
    }
    void operator=(ll a) {
        height_cnt = a;
        sm = 0;
    }
};
STN ST[4 * MAXN];
pair<LL, LL> lzy[4 * MAXN];
void STB(int id = 1, int l = 0, int r = N) {
    if (r - l < 2) {
        ST[id] = A[l];
        return;
    }
    int m = (l + r) >> 1, L = id << 1, R = L | 1;
    STB(L, l, m); STB(R, m, r);
    ST[id].merge(ST[L], ST[R]);
}
// Actualiza el nodo y guarda en lazy
void upd(int id, int l, int r, pair<LL, LL> x) {
    ST[id].sm += (r - l) * x.F + ST[id].height_cnt * x.S;
    lzy[id].F += x.F;
    lzy[id].S += x.S;
}
// Propaga el update en lazy
void shift(int id, int l, int r) {
    int m = (l + r) >> 1, L = id << 1, R = L | 1;
    upd(L, l, m, lzy[id]);
    upd(R, m, r, lzy[id]);
    lzy[id] = {0, 0};
}
STN STQ(int x, int y, int id = 1, int l = 0, int r = N) {
    if (x == l && y == r) return ST[id];
    shift(id, l, r);
    int m = (l + r) >> 1, L = id << 1, R = L | 1;
    if (x >= m) return STQ(x, y, R, m, r);
    if (y <= m) return STQ(x, y, L, l, m);
    STN res, ln = STQ(x, m, L, l, m), rn = STQ(m, y, R, m, r);
    return res.merge(ln, rn), res;
}
void STU(int x, int y, pair<LL, LL> v, int id = 1, int l = 0, int r = N) {
    if (x >= r || y <= l) return;
    if (x <= l && y >= r) {
        upd(id, l, r, v);
        return;
    }
    shift(id, l, r);
    int m = (l + r) >> 1, L = id << 1, R = L | 1;
    STU(x, y, v, L, l, m);
    STU(x, y, v, R, m, r);
    ST[id].merge(ST[L], ST[R]);
}

int main() {
    ri(N);
    FOR(i, 1, N) {
        int a, b; rii(a, b);
        --a; --b;
        G[a].pb(b);
        G[b].pb(a);
    }
    dfsSz(); dfsHLD();
    STB();

    int Q; ri(Q);
    while (Q--) {
        int t; ri(t);
        if (t == 0) {
            int x, y; rii(x, y);
            --x; --y;
            LL ans = 0;
            while (NXT[x] != NXT[y]) {
                if (H[NXT[x]] < H[NXT[y]])
                    swap(x, y);
                ans += STQ(IN[NXT[x]], IN[x] + 1).sm;
                x = F[NXT[x]];
            }
            if (H[x] < H[y])
                swap(x, y);
            ans += STQ(IN[y], IN[x] + 1).sm;
            print(ans);
            printf("\n");
        }
        else {
            int u, _v, _k; rii(u, _v), ri(_k); 
            --u;
            LL v = _v, k = _k;
            STU(IN[u], OUT[u], {v - k * H[u], k});
        }
    }



    return 0;
}