// https://acm.timus.ru/problem.aspx?space=1&num=2058

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

struct PalTree {
    static const int ASZ = 27;
    struct node {
        map<int, int> to;
        int len, link, oc = 0; // # occurrences of pal
        int slink = 0, diff = 0;
        array<int, 2> seriesAns;
        node(int _len, int _link) : len(_len), link(_link) {}
    };
    string s = "@"; vector<array<int, 2>> ans = {{0, INF}};
    vector<node> d = {{0, 1}, { -1, 0}}; // dummy pals of len 0,-1
    int last = 1;
    int getLink(int v) {
        while (s[sz(s) - d[v].len - 2] != s.back()) v = d[v].link;
        return v;
    }
    void updAns() { // serial path has O(log n) vertices
        ans.pb({INF, INF});
        for (int v = last; d[v].len > 0; v = d[v].slink) {
            d[v].seriesAns = ans[sz(s) - 1 - d[d[v].slink].len - d[v].diff];
            if (d[v].diff == d[d[v].link].diff)
                FOR(i, 0, 2) d[v].seriesAns[i] = min(d[v].seriesAns[i],
                                                     d[d[v].link].seriesAns[i]);
            // start of previous oc of link[v]=start of last oc of v
            FOR(i, 0, 2) ans[sz(ans) - 1][i] = min(ans[sz(ans) - 1][i],
                                                   d[v].seriesAns[i ^ 1] + 1);
        }
    }
    void addChar(char C) {
        s += C; int c = C - 'a'; last = getLink(last);
        if (d[last].to.find(c) == d[last].to.end()) {
            d.emplace_back(d[last].len + 2, d[getLink(d[last].link)].to[c]);
            d[last].to[c] = sz(d) - 1;
            auto& z = d.back(); z.diff = z.len - d[z.link].len;
            z.slink = z.diff == d[z.link].diff
                      ? d[z.link].slink : z.link;
        } // max suf with different dif
        last = d[last].to[c]; d[last].oc ++;
        updAns();
    }
    void numOc() { for (int i = sz(d) - 1; i >= 2; --i) d[d[i].link].oc += d[i].oc; }
};

int main() {
    string s; cin >> s;
    PalTree pt;
    for (auto c : s) pt.addChar(c);
    FOR(i, 1, sz(pt.ans)) {
        int a = pt.ans[i][1] == INF ? -1 : pt.ans[i][1];
        int b = pt.ans[i][0] == INF ? -2 : pt.ans[i][0];
        printf("%d %d\n", a, b);
    }

    return 0;
}