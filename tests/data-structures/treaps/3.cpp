// https://codeforces.com/gym/103469/problem/B

#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
 
#define FOR(i,n,m) for(int i = n; i < (int)m; i++)
#define ROF(i,n,m) for(int i = n; i > (int)m; i--)
#define ms(obj, val) memset(obj, val, sizeof(obj))
#define ri(a) scanf("%d", &a)
#define rii(a, b) ri(a), ri(b)
#define lri(a) scanf("%lld", &a)
#define lrii(a, b) lri(a), lri(b)
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x).size()
#define pb push_back
#define S second
#define F first
 
const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MOD = 998244353;
const int MAXN = 2e5+5;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 
 
 
void fastIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}
 
int N, W, K;
 
ll bin[10][10];
ll binomial(int n, int k) {
	if (n < k) return 0;
	if (n == k || k == 0) return 1;
	if (bin[n][k] != -1) return bin[n][k];
	return bin[n][k] = binomial(n-1, k) + binomial(n-1, k-1);
}
 
 
inline ll mult(ll a, ll b) {
	return a * b % MOD;
}
inline ll pot(ll a, ll e) {
	if (e == 0) return 1;
	if (e&1) return mult(pot(mult(a, a), e>>1), a);
	return pot(mult(a, a), e>>1);
}

using Treap = struct TNode*; // int and pool of nodes for speed
struct TNode {
    ll val, pri; Treap c[2]; // essential
    int sz; 
	array<ll, 6> sum;
	array<array<ll, 5>, 5> mod;
    bool flip = 0; // lazy update
    TNode(ll _val) {
        val = _val; pri = rng(); 
        sz = 1; c[0] = c[1] = nullptr;
		FOR(i,0,6) sum[i] = val;
		FOR(i,0,5) FOR(j,0,5) mod[i][j] = 0;
        mod[val%W][1]++;
    }
    ~TNode() { FOR(i,0,2) delete c[i]; }
};

int tsz(Treap t) { return t ? t->sz : 0; }
ll tsum(Treap t, int p) { return t ? t->sum[p] : 0; }
ll tmod(Treap t, int x, int y) { return t ? t->mod[x][y] : 0; }

Treap prop(Treap t) { // lazy propagation
    if (!t || !t->flip) return t;
    swap(t->c[0], t->c[1]);
    t->flip = 0; FOR(i,0,2) if (t->c[i]) t->c[i]->flip ^= 1;
    return t;
}

Treap upd(Treap t) { // modify here for different queries
    if (!t) return t;
    Treap a = t->c[0], b = t->c[1];
    // assert(!t->flip); prop(a), prop(b);

    int szl = tsz(a);
    ll val = t->val;
    t->sz = 1 + tsz(a) + tsz(b);
    
	FOR(i,0,K+1) {
		t->sum[i] = tsum(a, i) + mult(val, pot(szl+1, i));
		FOR(j,0,i+1) t->sum[i] += mult(tsum(b, j), mult(binomial(i, j), pot(szl+1, i-j))); 
		t->sum[i] %= MOD;
	}
 
	FOR(i,0,W) FOR(j,0,W) t->mod[i][j] = 0;
 
	FOR(i,0,W) FOR(j,0,W) {
		t->mod[i][j] += tmod(a, i, j);
		t->mod[i][(j+szl+1)%W] += tmod(b, i, j);
	}
 
	t->mod[val%W][(szl+1)%W]++;

    return t;
}

void tour(Treap t, vi &v) {
    if (!t) return;
    prop(t); tour(t->c[0], v); v.pb(t->val); tour(t->c[1], v);
}

pair<Treap, Treap> split(Treap t, int v) { // >= v goes to right
    if(!t) return {t, t};
    // prop(t);
    if (t->val >= v) {
        auto [a, b] = split(t->c[0], v); t->c[0] = b;
        return {a, upd(t)};
    }
    else {
        auto [a, b] = split(t->c[1], v); t->c[1] = a;
        return {upd(t), b};
    }
}

pair<Treap, Treap> splitsz(Treap t, int k) { // k nodes go to left
    if(!t) return {t, t};
    // prop(t);
    if (tsz(t->c[0]) >= k) {
        auto [a, b] = splitsz(t->c[0], k); t->c[0] = b;
        return {a, upd(t)};
    }
    else {
        auto [a, b] = splitsz(t->c[1], k-tsz(t->c[0])-1); t->c[1] = a;
        return {upd(t), b};
    }
}

Treap merge(Treap l, Treap r) { // keys in l < keys in r (or using splitsz)
    if (!l || !r) return l ? l : r;
    // prop(l), prop(r); 
    Treap t;
    if (l->pri > r->pri) l->c[1] = merge(l->c[1], r), t = l;
    else r->c[0] = merge(l, r->c[0]), t = r;
    return upd(t);
}

Treap ins(Treap t, int v) { // insert v (ignores if already in set)
    auto [a, b] = split(t, v);
    return merge(a, merge(new TNode(v), b));
}


Treap del(Treap t, int v) { // delete v 
    if (!t) return t;
    if (t->val == v) return merge(t->c[0], t->c[1]);

    if (v < t->val) t->c[0] = del(t->c[0], v);
    else t->c[1] = del(t->c[1], v);
    return upd(t);
}

void printTreap(Treap t) {
    vi ans; tour(t, ans);
    printf("[ ");
    for (auto x : ans) printf("%d ", x);
    printf("]\n");
}
 
ll a[MAXN];
 
int main() {
	ms(bin, -1);
	Treap t = nullptr;
 
	ri(N); rii(K, W);
	FOR(i,0,N) {
		lri(a[i]); 
		t = ins(t, a[i]);
	}
 
	int q;
	ri(q);
	while(q--) {
		int pos; ll val;
		ri(pos); pos--; lri(val);
 
		t = del(t, a[pos]);
        t = ins(t, (a[pos] = val));
 
		ll ans = tsum(t, K);
		FOR(i,0,W) FOR(j,0,W) ans -= mult(tmod(t, i, j), (i * pot(j, K) % W));
		ans %= MOD; ans += MOD; ans %= MOD;
 
		// printTree(t);
		printf("%lld\n", mult(ans, pot(W, MOD-2)));
	}
 
 
	return 0;
}