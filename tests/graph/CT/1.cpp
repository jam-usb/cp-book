// https://codeforces.com/problemset/problem/342/E

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

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pair<int, int>> piii;
typedef vector<int> vi;
typedef vector<pii> vii;

#define ri(a) scanf("%d", &a)
#define rii(a,b) scanf("%d %d", &a, &b)
#define riii(a,b,c) scanf("%d %d %d", &a, &b, &c)
#define rl(a) scanf("%lld", &a)
#define rll(a,b) scanf("%lld %lld", &a, &b)
#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define F first
#define S second
#define ms(obj,val) memset(obj,val,sizeof(obj))

const int INF = 0x3f3f3f3f;
const ll LLINF = 1e18;
const int MAXN = 1e5; // CAMBIAR ESTE

// GJNM
vector<int> G[MAXN]; int n;

// height
int height[MAXN];
void dfs_h(int x, int f = -1) {
    for (auto y : G[x]) {
        if (y == f)
            continue;
        height[y] = height[x] + 1;
        dfs_h(y, x);
    }
}

// LCA
int l = 17; // l = log(n)

int timer;
int tin[MAXN], tout[MAXN], anc[MAXN][18];

void dfs_lca(int v, int p) {
    tin[v] = ++timer;
    anc[v][0] = p;

    for (int i = 1; i <= l; ++i) anc[v][i] = anc[anc[v][i - 1]][i - 1];
    for (int w : G[v]) if (w != p) dfs_lca(w, v);

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

// distance
int dist(int u, int v) {
    return height[u] + height[v] - 2 * height[lca(u, v)];
}


// CENTROID TREE
bool tk[MAXN]; // already selected as a centroid
int fat[MAXN]; // father in centroid decomposition
int szt[MAXN]; // size of subtree
int calcsz(int x, int f) {
    szt[x] = 1;
    for (auto y : G[x])if (y != f && !tk[y])szt[x] += calcsz(y, x);
    return szt[x];
}
void cdfs(int x = 0, int f = -1, int sz = -1) { // O(nlogn)
    if (sz < 0)sz = calcsz(x, -1);
    for (auto y : G[x])if (!tk[y] && szt[y] * 2 >= sz) {
            szt[x] = 0; cdfs(y, f, sz); return;
        }
    tk[x] = true; fat[x] = f;
    for (auto y : G[x])if (!tk[y])cdfs(y, x);
}
void centroid() {ms(tk,false); cdfs();}


int cst[MAXN];

// updates and queries in centroid tree
void upd(int v) {
    int u = v;
    while (u != -1) {
        cst[u] = min(cst[u], dist(u, v));
        u = fat[u];
    }
}

int query(int v) {
    int u = v;
    int ans = 1000000000;
    while (u != -1) {
        ans = min(ans, cst[u] + dist(u, v));
        u = fat[u];
    }
    return ans;
}


int main() {
    int m;
    rii(n, m);
    FOR(i, 1, n) {
        int a, b; rii(a, b);
        a--, b--;
        G[a].pb(b);
        G[b].pb(a);
    }

    // dfs for height and lca
    dfs_lca(0, 0);
    dfs_h(0);

    // build centroid tree
    centroid();

    FOR(i, 0, n) {
        cst[i] = 1000000000;
    }

    upd(0);
    FOR(i, 0, m) {
        int t, v;
        rii(t, v);
        if (t == 1)
            upd(v - 1);
        else
            printf("%d\n", query(v - 1));
    }

    return 0;
}