// https://codeforces.com/problemset/problem/600/E

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

using namespace std;

typedef long long ll;
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

const int INF = 0x3f3f3f3f;
const ll LLINF = 1e18;
const int MAXN = 2e5 + 10; // CAMBIAR ESTE

// GJNM
int n;
int col[MAXN];
vi g[MAXN];

int sz[MAXN], st[MAXN], ft[MAXN], ver[MAXN], t;
void getsz(int v, int p) {
    sz[v] = 1;  // every vertex has itself in its subtree
    ver[t] = v;
    st[v] = t++;
    for (auto u : g[v])
        if (u != p) {
            getsz(u, v);
            sz[v] += sz[u]; // add size of child u to its parent(v)
        }
    ft[v] = t;
}

ll cnt[MAXN], ans[MAXN], mx_cnt[MAXN];
void dfs(int v, int p, bool keep) {
    int mx = -1, bigChild = -1;
    for (auto u : g[v])
        if (u != p && sz[u] > mx)
            mx = sz[u], bigChild = u;
    for (auto u : g[v])
        if (u != p && u != bigChild)
            dfs(u, v, 0);  // run a dfs on small childs and clear them from cnt
    if (bigChild != -1) {
        dfs(bigChild, v, 1);  // bigChild marked as big and not cleared from cnt
        mx_cnt[v] = mx_cnt[bigChild];
        ans[v] = ans[bigChild];
    }
    for (auto u : g[v])
        if (u != p && u != bigChild) {
            for (int p = st[u]; p < ft[u]; p++) {
                cnt[ col[ ver[p] ] ]++;
                if (cnt[ col[ ver[p] ] ] > mx_cnt[v]) {
                    mx_cnt[v] = cnt[ col[ ver[p] ] ];
                    ans[v] = col[ ver[p] ];
                }
                else if (cnt[ col[ ver[p] ] ] == mx_cnt[v]) {
                    ans[v] += col[ ver[p] ];
                }
            }
        }
    cnt[ col[v] ]++;
    if (cnt[ col[ v ] ] > mx_cnt[v]) {
        mx_cnt[v] = cnt[ col[ v ] ];
        ans[v] = col[ v ];
    }
    else if (cnt[ col[ v ] ] == mx_cnt[v]) {
        ans[v] += col[ v ];
    }
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    if (keep == 0)
        for (int p = st[v]; p < ft[v]; p++)
            cnt[ col[ ver[p] ] ]--;
}


int main() {
    ri(n);
    FOR(i, 0, n) {
        ri(col[i]);
    }
    FOR(i, 1, n) {
        int a, b; rii(a, b); a--, b--;
        g[a].pb(b), g[b].pb(a);
    }

    getsz(0, 0);
    dfs(0, 0, 1);
    FOR(i, 0, n) {
        printf("%lld ", ans[i]);
    } printf("\n");


    return 0;
}