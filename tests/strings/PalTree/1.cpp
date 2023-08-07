// https://codeforces.com/group/j1UosVRZar/contest/288671/problem/G

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
    static const int ASZ = 26;
    struct node {
        array<int, ASZ> to = array<int, ASZ>();
        int len, link, oc = 0; // # occurrences of pal
        int slink = 0, diff = 0;
		int par, parc;
        int chain_sz = 0;
        array<int, 2> seriesAns;
        node(int _len, int _link) : len(_len), link(_link) {}
    };
    string s = "@"; vector<array<int, 2>> ans = {{0, INF}};
    vector<node> d = {{0, 1}, { -1, 0}}; // dummy pals of len 0,-1
    vi lasts = {1};
    int oc = 0;
    int getLink(int v) {
        while (s[sz(s) - d[v].len - 2] != s.back()) v = d[v].link;
        return v;
    }
    void addChar(char C) {
        s += C; int c = C - 'a';
        int last = lasts.back();
        last = getLink(last);
        if (!d[last].to[c]) {
            d.emplace_back(d[last].len + 2, d[getLink(d[last].link)].to[c]);
            d[last].to[c] = sz(d) - 1;
            d[sz(d) - 1].par = last;
            d[sz(d) - 1].parc = c;
            d[sz(d) - 1].chain_sz = d[ d[sz(d) - 1].link ].chain_sz + 1;
            //auto& z = d.back(); z.diff = z.len - d[z.link].len;
            //z.slink = z.diff == d[z.link].diff
            //          ? d[z.link].slink : z.link;
        } // max suf with different dif
        last = d[last].to[c];
        d[last].oc++;
        oc += d[last].chain_sz;
        lasts.pb(last);
        //updAns();
    }
    void rmChar() {
        s.pop_back();
        int last = lasts.back();
        lasts.pop_back();

        d[last].oc--;
        oc -= d[last].chain_sz;

        if (d[last].oc == 0)
            d[ d[last].par ].to[ d[last].parc ] = 0;
    }
};
int main() {
    int q; ri(q);
    string s; cin >> s;
    PalTree pt;
    for (auto c : s) {
        if (c == '-') pt.rmChar();
        else pt.addChar(c);
        printf("%d ", pt.oc);
    }
    printf("\n");
    return 0;
}