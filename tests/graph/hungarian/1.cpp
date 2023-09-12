// https://cses.fi/problemset/task/2129/

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
#define all(s) s.begin(),s.end()
#define sz(s) (int)s.size()
 
const ll LLINF = 1e18;
const int MAXN = 210; // CAMBIAR ESTE
//mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
 
typedef int T;
typedef vector<T> vd;
const T INF = 1e8;  // for maximum set INF to 0, and negate costs
bool zero(T x) { return x==0; }  // change to x==0, for ints/ll
struct Hungarian {
    int n;
    vector<vd> cs;
    vi L, R;
    Hungarian(int N, int M) : n(max(N, M)), cs(n, vd(n)), L(n), R(n) {
        FOR(x, 0, N) FOR(y, 0, M) cs[x][y] = INF;
    }
    void set(int x, int y, T c) { cs[x][y] = c; }
    T solve() {
        int mat = 0;
        vd ds(n), u(n), v(n);
        vi dad(n), sn(n);
        FOR(i, 0, n) u[i] = *min_element(all(cs[i]));
        FOR(j, 0, n) {
            v[j] = cs[0][j] - u[0];
            FOR(i, 1, n) v[j] = min(v[j], cs[i][j] - u[i]);
        }
        L = R = vi(n, -1);
        FOR(i, 0, n) FOR(j, 0, n)
            if (R[j] == -1 && zero(cs[i][j] - u[i] - v[j])) {
                L[i] = j;
                R[j] = i;
                mat++;
                break;
            }
        for (; mat < n; mat++) {
            int s = 0, j = 0, i;
            while (L[s] != -1) s++;
            fill(all(dad), -1);
            fill(all(sn), 0);
            FOR(k, 0, n) ds[k] = cs[s][k] - u[s] - v[k];
            for (;;) {
                j = -1;
                FOR(k, 0, n)
                    if (!sn[k] && (j == -1 || ds[k] < ds[j])) j = k;
                sn[j] = 1;
                i = R[j];
                if (i == -1) break;
                FOR(k, 0, n)
                    if (!sn[k]) {
                        auto new_ds = ds[j] + cs[i][k] - u[i] - v[k];
                        if (ds[k] > new_ds) {
                            ds[k] = new_ds;
                            dad[k] = j;
                        }
                    }
            }
            FOR(k, 0, n)
                if (k != j && sn[k]) {
                    auto w = ds[k] - ds[j];
                    v[k] += w;
                    u[R[k]] -= w;
                }
            u[s] += ds[j];
            while (dad[j] >= 0) {
                int d = dad[j];
                R[j] = R[d];
                L[R[j]] = j;
                j = d;
            }
            R[j] = s;
            L[s] = j;
        }
        T value = 0;
        FOR(i, 0, n) value += cs[i][L[i]];
        return value;
    }
};

 
int main() {
    int n; ri(n);
    Hungarian h(n,n);
    FOR(i,0,n) FOR(j,0,n) {
        int a; ri(a);
        h.set(i,j,a);
    }
    cout << h.solve() << endl;
    FOR(i,0,n) cout << i + 1 << " " << h.L[i] + 1 << endl;
    return 0;
}