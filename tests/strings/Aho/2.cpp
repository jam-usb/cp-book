// https://www.codechef.com/problems/FAVNUM

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int das;
#define FOR(i,n,m) for(int i = n; i < (int)m; i++)
#define ROF(i,n,m) for(int i = n; i > (int)m; i--)
#define ms(obj,val) memset(obj,val,sizeof(obj))
#define ri(a) das=scanf("%d", &a)
#define rii(a,b) ri(a), ri(b)
#define lri(a) das=scanf("%lld", &a)
#define lrii(a,b) lri(a), lri(b)
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x).size()
#define pb push_back
#define S second
#define F first

const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MOD = 1e9+7;
const int MAXN = 1e5+52;

void fastIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}

struct ACfixed { // fixed alphabet
    static const int ASZ = 10;
    struct node { array<int, ASZ> to; int link; int out; bool leaf = false;};
    vector<node> d = {{}};
    int add(string s) { // add word
        int v = 0;
        for (auto C : s) {
            int c = C - '0';
            if (!d[v].to[c]) d[v].to[c] = sz(d), d.emplace_back();
            v = d[v].to[c];
        }
        d[v].leaf = true;
        return v;
    }
    void init() { // generate links
        d[0].link = -1;
        d[0].out = -1;
        queue<int> q; q.push(0);
        while (sz(q)) {
            int v = q.front(); q.pop();
            FOR(c, 0, ASZ) {
                int u = d[v].to[c]; if (!u) continue;
                d[u].link = d[v].link == -1 ? 0 : d[d[v].link].to[c];
                q.push(u);
            }
            if (v) FOR(c, 0, ASZ) if (!d[v].to[c])
                    d[v].to[c] = d[d[v].link].to[c];
            if (v) {
                if (d[d[v].link].leaf) d[v].out = d[v].link;
                else d[v].out = d[d[v].link].out;
            if (v)
                d[v].leaf |= d[d[v].link].leaf;
            }
        }
    }
};

ll L, R, K, N;
ACfixed AHO;

int NA;
vi A;
ll DP[20][1200][3][2];
ll f(int p, int ahop, int c, int v) {
    if (DP[p][ahop][c][v] != -1) return DP[p][ahop][c][v];
    ll &ret = DP[p][ahop][c][v];
    if (p == NA) return ret = 0;


    ret = 0;
    if (c == 0) { // lower than A[0..p-1]
        FOR(i, 0, 10) {
            int nxt = AHO.d[ahop].to[i];
            int newv = v | AHO.d[nxt].leaf;
            if (newv)
                ret++;
            ret += f(p + 1, nxt, 0, newv);
        }
    }
    else if (c == 1) { // same than A[0..p-1]
        FOR(i, p == 0, 10) {
            int nxt = AHO.d[ahop].to[i];
            int newv = v | AHO.d[nxt].leaf;
            if (newv && (p + 1 < NA || i <= A[p]))
                ret++;
            if (i < A[p])
                ret += f(p + 1, nxt, 0, newv);
            else if (i == A[p])
                ret += f(p + 1, nxt, 1, newv);
            else
                ret += f(p + 1, nxt, 2, newv);
        }
    }
    else { // higher than A[0..p-1]
        FOR(i, 0, 10) {
            int nxt = AHO.d[ahop].to[i];
            int newv = v | AHO.d[nxt].leaf;
            if (newv && p + 1 < NA)
                ret++;
            ret += f(p + 1, nxt, 2, newv);
        }
    }
    return ret;
}

bool valid(ll x) {
    memset(DP, -1, sizeof(DP));
    A.clear();
    while (x > 0) {
        A.pb(x % 10);
        x /= 10;
    }
    reverse(all(A));
    NA = sz(A);
    ll hicnt = f(0, 0, 1, 0);

    memset(DP, -1, sizeof(DP));
    A.clear();
    x = L;
    while (x > 0) {
        A.pb(x % 10);
        x /= 10;
    }
    reverse(all(A));
    NA = sz(A);
    ll locnt = f(0, 0, 1, 0);

    return (hicnt - locnt >= K);
}

int main() {
    lrii(L, R), lrii(K, N); --L;
    FOR(_, 0, N) {
        string s; cin >> s;
        AHO.add(s);
    }
    AHO.init();

    if (!valid(R)) {
        printf("no such number\n");
        return 0;
    }

    ll lo = L + 1, hi = R;
    while (lo < hi) {
        ll mi = lo + (hi - lo) / 2;
        if (valid(mi))
            hi = mi;
        else
            lo = mi + 1;
    }
    printf("%lld\n", lo);
    return 0;
}