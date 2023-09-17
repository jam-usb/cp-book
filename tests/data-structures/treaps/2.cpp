// https://www.spoj.com/problems/TREAP/

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

const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MOD = 1e9+7;
const int MAXN = 2e5+5;
mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

void fastIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}

using Treap = struct TNode*; // int and pool of nodes for speed
struct TNode {
    ll val, pri; Treap c[2]; // essential
    int sz;
    ll mindiff, mn, mx;
    bool flip = 0; // lazy update
    TNode(int _val) {
        val = mn = mx = _val; pri = rng(); 
        mindiff = INF;
        sz = 1; c[0] = c[1] = nullptr;
    }
    ~TNode() { FOR(i,0,2) delete c[i]; }
};

int tsz(Treap t) { return t ? t->sz : 0; }
ll tmn(Treap t) { return t ? t->mn : 2ll*INF; }
ll tmx(Treap t) { return t ? t->mx : -2ll*INF; }
ll tmindiff(Treap t) { return t ? t->mindiff : 2ll*INF; }

Treap prop(Treap t) { // lazy propagation
    if (!t || !t->flip) return t;
    swap(t->c[0], t->c[1]);
    t->flip = 0; FOR(i,0,2) if (t->c[i]) t->c[i]->flip ^= 1;
    return t;
}

Treap upd(Treap t) { // modify here for different queries
    if (!t) return t;
    Treap a = t->c[0], b = t->c[1];
    assert(!t->flip); prop(a), prop(b);
    t->sz = 1 + tsz(a) + tsz(b);
    t->mn = min(min(tmn(a), tmn(b)), t->val);
    t->mx = max(max(tmx(a), tmx(b)), t->val);
    t->mindiff = min(tmindiff(a), tmindiff(b));
    t->mindiff = min(t->mindiff, min(t->val - tmx(a), tmn(b) - t->val));
    return t;
}

void tour(Treap t, vi &v) {
    if (!t) return;
    prop(t); tour(t->c[0], v); v.pb(t->val); tour(t->c[1], v);
}

pair<Treap, Treap> split(Treap t, int v) { // >= v goes to right
    if(!t) return {t, t};
    prop(t);
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
    prop(t);
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
    prop(l), prop(r); Treap t;
    if (l->pri > r->pri) l->c[1] = merge(l->c[1], r), t = l;
    else r->c[0] = merge(l, r->c[0]), t = r;
    return upd(t);
}

Treap ins(Treap t, int v) { // insert v (ignores if already in set)
    auto [a, b] = split(t, v); auto [c, d] = split(b, v+1);
    return merge(a, merge(new TNode(v), d));
}

Treap del(Treap t, int v) { // delete v (deletes all with key v)
    auto [a, b] = split(t, v); auto [c, d] = split(b, v+1);
    return merge(a, d);
}

char tmp[8];

int main(){
    int N;
    ri(N);
    Treap t = nullptr;

    FOR(i,0,N) {
        scanf("%s", tmp);
        if (tmp[0] == 'I') {
            int v; ri(v);
            t = ins(t, v);
        }
        if (tmp[0] == 'D') {
            int v; ri(v);
            t = del(t, v);
        }
        if (tmp[0] == 'X') {
            int a, b; rii(a, b);
            if (a == b) { printf("-1\n"); continue; }
            auto [aux, rtree] = splitsz(t, b+1);
            auto [ltree, mtree] = splitsz(aux, a);

            printf("%lld\n", tmx(mtree) - tmn(mtree));
            
            t = merge(ltree, merge(mtree, rtree));
        }
        if (tmp[0] == 'N') {
            int a, b; rii(a, b);
            if (a == b) { printf("-1\n"); continue; }
            auto [aux, rtree] = splitsz(t, b+1);
            auto [ltree, mtree] = splitsz(aux, a);

            printf("%lld\n", tmindiff(mtree));
            
            t = merge(ltree, merge(mtree, rtree));
        }

    }
    

	return 0;
}
