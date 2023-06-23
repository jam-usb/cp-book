// https://www.spoj.com/problems/QTREE/

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
 
int dasdsa;
#define FOR(i,n,m) for(int i = n; i < (int)m; i++)
#define ROF(i,n,m) for(int i = n; i > (int)m; i--)
#define ms(obj,val) memset(obj,val,sizeof(obj))
#define ri(a) dasdsa=scanf("%d", &a)
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
const int MAXN = 1e5+5;
 
 
int N, A[MAXN];
vi G[MAXN];
vector<tuple<int, int, int>> E;
 
struct STN {
    int val;
    void merge(STN& L, STN& R) {
        val = max(L.val, R.val);
    }
    void operator=(int a) {
        val = a;
    }
};
STN ST[4 * MAXN];
void STB(int id = 1, int l = 0, int r = N) {
    if (r - l < 2) {
        ST[id] = A[l];
        return;
    }
    int m = (l + r) >> 1, L = id << 1, R = L | 1;
    STB(L, l, m); STB(R, m, r);
    ST[id].merge(ST[L], ST[R]);
}
STN STQ(int x, int y, int id = 1, int l = 0, int r = N) {
    if (x == l && y == r) return ST[id];
    int m = (l + r) >> 1, L = id << 1, R = L | 1;
    if (x >= m) return STQ(x, y, R, m, r);
    if (y <= m) return STQ(x, y, L, l, m);
    STN res, ln = STQ(x, m, L, l, m), rn = STQ(m, y, R, m, r);
    return res.merge(ln, rn), res;
}
void STU(int p, int x, int id = 1, int l = 0, int r = N) {
    if (r - l < 2) {
        ST[id] = x;
        return;
    }
    int m = (l + r) >> 1, L = id << 1, R = L | 1;
    if (p < m) STU(p, x, L, l, m);
    else STU(p, x, R, m, r);
    ST[id].merge(ST[L], ST[R]);
}
 
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
    for (auto u : G[v]) if (u != p) {
            NXT[u] = (u == G[v][0] ? NXT[v] : u);
            dfsHLD(u, v);
        }
    OUT[v] = T;
}
 
void upd(int u, int v, int c) {
	if (F[v] != u) swap(u,v);
	STU(IN[v], c);
}
 
void solve() {
	ri(N);
 
	FOR(i,0,N) G[i].clear();
	E.clear();
 
	FOR(i,1,N) {
		int u, v, c; rii(u,v), ri(c); --u, --v;
		G[u].pb(v);
		G[v].pb(u);
		E.pb({u,v,c});
	}
	T = 0;
	dfsSz();
	dfsHLD();
 
	for(auto [u, v, c] : E) {
		if (F[u] != v) swap(u, v);
		A[IN[u]] = c;
	}
	STB();
 
	char s[22];
	while(69) {
		scanf("%s", s);
		if (s[0] == 'D') break;
 
		if (s[0] == 'C') {
			int i, ci; rii(i, ci);
			auto [u, v, _] = E[i-1];
			upd(u, v, ci);
			continue;
		}
 
		int mx = 0;
 
		int u,v; rii(u,v); --u, --v;
		while(NXT[u] != NXT[v]) {
			if (H[NXT[u]] < H[NXT[v]]) swap(u,v);
			mx = max(mx, STQ(IN[NXT[u]], IN[u] + 1 ).val);
			u = F[NXT[u]];
		}
		if (H[u] < H[v]) swap(u,v);
		if (u != v) mx = max(mx, STQ(IN[v] + 1, IN[u] + 1 ).val);
 
		printf("%d\n", mx);
	}
}
 
int main(){
	int t; ri(t);
	while(t--) solve();
	return 0;
}
  