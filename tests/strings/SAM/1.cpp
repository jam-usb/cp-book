// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3664

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

void fastIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}

struct SUF_AUT {
    static const int ASZ = 26;
    struct node { int len, link; array<int, ASZ> to; int cnt;};
    vector<node> d = {{}};
    int last;
    void init(string S) {
        last = d[0].len = 0;
        d[0].link = -1;
        d[0].to.fill(0);
        d[0].cnt = 0;
        for (auto C : S) {
            int c = C - 'a', v = sz(d), p = last; // Be careful with mapping char to int
            d.emplace_back();
            d[v].len = d[last].len + 1;
            d[v].cnt = 1;
            for (; p > -1 && !d[p].to[c]; p = d[p].link)
                d[p].to[c] = v;
            if (p == -1) {
                d[v].link = 0;
            }
            else {
                int q = d[p].to[c];
                if (d[p].len + 1 == d[q].len) {
                    d[v].link = q;
                    d[q].cnt++;
                }
                else {
                    int qq = sz(d);
                    d.emplace_back();
                    d[qq].len = d[p].len + 1;
                    d[qq].to = d[q].to;
                    d[qq].cnt = d[q].cnt;
                    d[qq].link = d[q].link;
                    d[v].link = d[q].link = qq;
                    for (; p > -1 && d[p].to[c] == q; p = d[p].link)
                        d[p].to[c] = qq;
                }
            }
			for (p = d[v].link; p > -1; p = d[p].link)
                d[p].cnt++;
            last = v;
        }
    }
};


void solve() {
    string s; cin >> s;
    SUF_AUT sa; sa.init(s);
    int ans = 0;
    for (auto x : sa.d)
        if (x.len > ans && x.cnt > 1) ans = x.len;
    printf("%d\n", ans);
}


int main() {
    int t; ri(t);
    while (t--)
        solve();
    return 0;
}