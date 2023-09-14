// https://www.spoj.com/problems/SCITIES/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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

const ll INFLL = 1e18;
const int MOD = 1e9+7;
const int MAXN = 2e5+5;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

void fastIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}

typedef int T;
const int INF = 0;
typedef vector<T> vd;
bool zero(T x) { return x == 0; }  // change to x==0, for ints/ll
struct Hungarian {
    int n;
    vector<vd> cs;
    vi L, R; // here are the matches
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


int main(){
    int t; ri(t);
    while(t--) {
        int n, m; cin >> n >> m;
        Hungarian H(n,m);
        while (true) {
            int u, v, g;
            cin >> u >> v >> g;
            if (u == 0 && v == 0 && g == 0) break;
            H.set(u-1, v-1, -g);
        }

        cout << -H.solve() << endl;

        
    }

	return 0;
}

