// https://codeforces.com/problemset/problem/570/D

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
const int MAXN = 5e5 + 10; // CAMBIAR ESTE

// GJNM
struct QUERY {
    int h, ind;

};
int N, M, T;
vi G[MAXN];
int H[MAXN];
char S[MAXN];
vector<QUERY> QS[MAXN];
bool ANS[MAXN];

int sz[MAXN], st[MAXN], ft[MAXN], ver[MAXN], t;
void getsz(int v) {
    sz[v] = 1;  // every vertex has itself in its subtree
    ver[t] = v;
    st[v] = t++;
    for (auto u : G[v]) {
        H[u] = H[v] + 1;
        getsz(u);
        sz[v] += sz[u]; // add size of child u to its parent(v)
    }
    ft[v] = t;
}


int cnt[30 * MAXN], col[MAXN];
void dfs(int v, bool keep) {
    int mx = -1, bigChild = -1;
    for (auto u : G[v])
        if (sz[u] > mx)
            mx = sz[u], bigChild = u;
    for (auto u : G[v])
        if (u != bigChild)
            dfs(u, 0);  // run a dfs on small childs and clear them from cnt
    if (bigChild != -1)
        dfs(bigChild, 1);  // bigChild marked as big and not cleared from cnt
    for (auto u : G[v])
        if (u != bigChild)
            for (int p = st[u]; p < ft[u]; p++)
                cnt[ col[ ver[p] ] ]++;
    cnt[ col[v] ]++;
    //now cnt[c] is the number of vertices in subtree of vertex v that has color c. You can answer the queries easily.
    for (auto q : QS[v]) {
        int h = q.h, j = q.ind;
        int odd = 0;
        FOR(i, 0, 26) odd += cnt[30 * h + i] & 1;
        ANS[j] = odd <= 1;
    }

    if (keep == 0)
        for (int p = st[v]; p < ft[v]; p++)
            cnt[ col[ ver[p] ] ]--;
}

int main() {
    rii(N, M);
    FOR(i, 1, N) {
        int tmp; ri(tmp);
        G[tmp - 1].pb(i);
    }
    dadsadasda = scanf("%s", S);
    FOR(i, 0, M) {
        int v, h; rii(v, h);
        QS[v - 1].pb({h - 1, i});
    }
    getsz(0);
    FOR(i, 0, N) col[i] = H[i] * 30 + (S[i] - 'a');
    dfs(0, 1);
    FOR(i, 0, M) {
        if (ANS[i])
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}