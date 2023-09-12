// https://codeforces.com/gym/100570/problem/F

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <math.h>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include <unordered_map>
#include <assert.h>
#include <array>
#include <random>
#include <chrono>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, pair<int, int>> piii;
typedef vector<int> vi;
typedef vector<pii> vii;

int dadsadasda;

#define ri(a) dadsadasda=scanf("%d", &a)
#define rii(a,b) dadsadasda=scanf("%d %d", &a, &b)
#define riii(a,b,c) dadsadasda=scanf("%d %d %d", &a, &b, &c)
#define rl(a) dadsadasda=scanf("%lld", &a)
#define rll(a,b) dadsadasda=scanf("%lld %lld", &a, &b)
#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define F first
#define S second
#define ALL(s) s.begin(),s.end()
#define SZ(s) (int)s.size()
#define ms(obj,val) memset(obj,val,sizeof(obj))

const int INF = 0x3f3f3f3f;
const ll LLINF = 1e18;
const int MAXN = 1e5 + 69; // CAMBIAR ESTE
//mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

// GJNM
int N, Q;

vector<pair<int, ll>> G[MAXN];

int l = 22;
int timer; // Tiempos de entrada y salida de cada nodo y su ancestro a dist 2**i
int tin[MAXN], tout[MAXN], anc[MAXN][ 22 + 1 ];
ll H[MAXN];

void dfs(int v, int p) { // Se inicializa con dfs(1,1)
    tin[v] = ++timer;
    anc[v][0] = p;

    for (int i = 1; i <= l; ++i) anc[v][i] = anc[ anc[v][i - 1] ][i - 1];
    for (auto [w, c] : G[v]) if (w != p) {
            H[w] = H[v] + c;
            dfs(w, v);
        }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v) { return tin[u] <= tin[v] && tout[u] >= tout[v]; }

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;

    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(anc[u][i], v)) {
            u = anc[u][i];
        }
    }
    return anc[u][0];
}

ll dst(int u, int v) {
    return H[u] + H[v] - 2 * H[lca(u, v)];
}




bool tk[MAXN]; // already selected as a centroid
int fat[MAXN]; // father in centroid decomposition
int szt[MAXN]; // size of subtree
int calcsz(int x, int f) {
    szt[x] = 1;
    for (auto [y,_] : G[x])if (y != f && !tk[y])szt[x] += calcsz(y, x);
    return szt[x];
}
void cdfs(int x = 0, int f = -1, int sz = -1) { // O(nlogn)
    if (sz < 0)sz = calcsz(x, -1);
    for (auto [y,_] : G[x])if (!tk[y] && szt[y] * 2 >= sz) {
            szt[x] = 0; cdfs(y, f, sz); return;
        }
    tk[x] = true; fat[x] = f;
    for (auto [y,_] : G[x])if (!tk[y])cdfs(y, x);
}
void centroid() {ms(tk,false); cdfs();}


vector<ll> DSTs[MAXN];
vector<ll> DST2s[MAXN];

int main() {
    rii(N, Q);
    FOR(_, 1, N) {
        int a, b; ll c;
        rii(a, b); rl(c);
        G[a - 1].pb({b - 1, c});
        G[b - 1].pb({a - 1, c});
    }
    dfs(0, 0);
    centroid();
    FOR(i, 0, N) {
        int u = i;
        do {
            DSTs[u].pb(dst(i, u));
            u = fat[u];
        } while (u != -1);
        
        u = i;
        int v = fat[i];
        while (v != -1) {
            DST2s[u].pb(dst(i, v));
            u = fat[u];
            v = fat[v];
        }
    }
    FOR(i, 0, N) sort(ALL(DSTs[i]));
    FOR(i, 0, N) sort(ALL(DST2s[i]));

    while (Q--) {
        int u; ll c;
        ri(u); rl(c); --u;
        int ans = ub(ALL(DSTs[u]), c) - DSTs[u].begin();
        int f = u, gf = fat[u];
        while (gf != -1) {
            ll d = dst(u, gf);
            ans += ub(ALL(DSTs[gf]), c - d) - DSTs[gf].begin();
            ans -= (ub(ALL(DST2s[f]), c - d) - DST2s[f].begin());
            f = gf;
            gf = fat[gf];
        }
        printf("%d\n", ans);
    }


    return 0;
}