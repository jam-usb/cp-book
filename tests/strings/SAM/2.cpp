// https://codeforces.com/contest/427/problem/D

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
    static const int ASZ = 27;
    struct node { int len, link; array<int, ASZ> to; int cnt, cnt2;};
    vector<node> d = {{}};
    int last;
     void init(string S) {
        last = d[0].len = 0;
        d[0].link = -1;
        bool found = false;;
        for (auto C : S) {
            int c = C - 'a', v = sz(d), p = last; // Be careful with mapping char to int
            d.emplace_back();
            d[v].len = d[last].len + 1;
            d[v].cnt = 1;
            found |= c == 26;
            d[v].cnt2 = !found;
            for (; p > -1 && !d[p].to[c]; p = d[p].link)
                d[p].to[c] = v;
            if (p == -1) {
                d[v].link = 0;
            }
            else {
                int q = d[p].to[c];
                if (d[p].len + 1 == d[q].len) {
                    d[v].link = q;
                }
                else {
                    int qq = sz(d);
                    d.emplace_back();
                    d[qq].len = d[p].len + 1;
                    d[qq].to = d[q].to;
                    d[qq].link = d[q].link;
                    d[qq].cnt = 0;
                    d[qq].cnt2 = 0;
                    d[v].link = d[q].link = qq;
                    for (; p > -1 && d[p].to[c] == q; p = d[p].link)
                        d[p].to[c] = qq;
                }
            }
            last = v;
        }

        vii ord;
        FOR(i, 0, sz(d)) ord.pb({ -d[i].len, i});
        sort(all(ord));
        for (auto [_, x] : ord) if (x > 0) {
                d[ d[x].link ].cnt += d[x].cnt;
                d[ d[x].link ].cnt2 += d[x].cnt2;
            }
        int mn = INF;
        FOR(i, 1, sz(d)) {
            if (d[i].cnt == 2 && d[i].cnt2 == 1) {
                mn = min(mn, d[d[i].link].len + 1);
            }
        }
        printf("%d\n", (mn == INF ? -1 : mn));
    }
};
 
int main() {
    string a, b; cin >> a >> b;
    SUF_AUT sa; sa.init(a + (char)('a' + 26) + b);
    return 0;
}