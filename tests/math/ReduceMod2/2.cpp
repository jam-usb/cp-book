// https://codeforces.com/group/gXivUSZQpn/contest/337359/problem/B

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
#define sz(s) (int)s.size()

const int INF = 0x3f3f3f3f;
const ll LLINF = 1e18;
const int MAXN = 1e5 + 10; // CAMBIAR ESTE

// GJNM
int N;
ll A[MAXN];

/**
 * Author: not sure
 * Description: not needed
 */

void reduceMod2(vector<vi>& x) {
    int n = sz(x), m = sz(x[0]);
    int i = 0, j = 0, mod = 2;
    while (i < n && j < m) {
        int l = i;
        FOR(k, i + 1, n)if (x[k][j] > x[l][j])l = k;
        if (x[l][j] == 0) {j++; continue;}
        if (l != i) {swap(x[i], x[l]);}
        FOR(k, 0, n) {
            if (k == i)continue;
            for (int _l = m - 1; _l >= j; _l--)
                x[k][_l] = (x[k][_l] - x[k][j] * x[i][_l] + mod) & 1;
        }
        i++; j++;
    }
}

int main() {
    ri(N);
    FOR(i, 0, N) rl(A[i]);

    vector<vi> x(N, vi(63, 0));

    FOR(i, 0, N) {
        FOR(b, 0, 62) {
            if ((A[i] >> b) & 1) x[i][61 - b] = 1;
        }
    }

    reduceMod2(x);

    ll ans = 0;
    FOR(i, 0, N) FOR(b, 0, 62) if (x[i][b]) {
        ans ^= (1ll << (61 - b));
    }
    printf("%lld\n", ans);
    return 0;
}