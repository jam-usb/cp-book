// https://codeforces.com/contest/163/problem/E

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
const int MAXN = 1e6+52;

void fastIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}

int Q, K;
vi G[MAXN];
int IN[MAXN], OUT[MAXN];
int IND[MAXN], ADDED[MAXN];
int _t;

void dfs(int u) {
    IN[u] = _t++;
    for(int v : G[u]) dfs(v);
    OUT[u] = _t;
}

ll BIT[MAXN], LOGN = log2(MAXN)+1;
void updBIT(int p, ll val){ 
    p++;	
    for(; p < MAXN; p += p&-p) BIT[p] += val;
}

ll sumBIT(int p){
    p++;
    ll ret = 0;
    for(; p; p -= p&-p) 
    	ret += BIT[p];
    return ret;
}

void add(int u) {
    if (ADDED[u]) return;
    ADDED[u] = 1;
    updBIT(IN[u], 1);
    updBIT(OUT[u], -1);
}
void rem(int u) {
    if (!ADDED[u]) return;
    ADDED[u] = 0;
    updBIT(IN[u], -1);
    updBIT(OUT[u], 1);
}

struct ACfixed { // fixed alphabet
    static const int ASZ = 26;
    struct node { array<int, ASZ> to; int link; int out; bool leaf = false;;};
    vector<node> d = {{}};
    int add(string s, int ind) { // add word
        int v = 0;
        for (auto C : s) {
            int c = C - 'a';
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
                G[d[v].link].pb(v);
            }
        }
    }
};

ACfixed aho;

int main(){
    rii(Q,K);
    FOR(i,0,K) {
        string s; cin >> s;
        IND[i] = aho.add(s, i);
    }
    aho.init();
    dfs(0);
    FOR(i,0,K) {
        add(IND[i]);        
    }

    while (Q--) {
        char t;
        das = scanf("%*c%c", &t);
        if (t == '-') {
            int v; ri(v); --v;
            rem(IND[v]);
        }
        else if (t == '+') {
            int v; ri(v); --v;
            add(IND[v]);
        }
        else {
            string s; cin >> s;
            ll ans = 0;
            int p = 0;
            for (auto c : s) {
                p = aho.d[p].to[c - 'a'];
                ans += sumBIT(IN[p]);
            }
            printf("%lld\n", ans);
        }
    }



	return 0;
}
