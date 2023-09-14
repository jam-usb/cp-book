// https://codeforces.com/problemset/problem/863/F

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

const int INF = 0x3f3f3f3f;
const ll LLINF = 1e18;
const int MAXN = 1e5; // CAMBIAR ESTE

typedef ll tf;
typedef ll tc;
const tf INFFLOW=1e9;
const tc INFCOST=1e9;
struct MCF{
	int n;
	vector<tc> prio, pot; vector<tf> curflow; vector<int> prevedge,prevnode;
	priority_queue<pair<tc, int>, vector<pair<tc, int>>, greater<pair<tc, int>>> q;
	struct edge{int to, rev; tf f, cap; tc cost;};
	vector<vector<edge>> g;
	MCF(int n):n(n),prio(n),curflow(n),prevedge(n),prevnode(n),pot(n),g(n){}
	void add_edge(int s, int t, tf cap, tc cost) {
		g[s].pb((edge){t,sz(g[t]),0,cap,cost});
		g[t].pb((edge){s,sz(g[s])-1,0,0,-cost});
	}
	pair<tf,tc> get_flow(int s, int t) {
		tf flow=0; tc flowcost=0;
		while(1){
			q.push({0, s});
			fill(all(prio),INFCOST); 
			prio[s]=0; curflow[s]=INFFLOW;
			while(!q.empty()) {
				auto cur=q.top();
				tc d=cur.F;
				int u=cur.S;
				q.pop();
				if(d!=prio[u]) continue;
				for(int i=0; i<sz(g[u]); ++i) {
					edge &e=g[u][i];
					int v=e.to;
					if(e.cap<=e.f) continue;
					tc nprio=prio[u]+e.cost+pot[u]-pot[v];
					if(prio[v]>nprio) {
						prio[v]=nprio;
						q.push({nprio, v});
						prevnode[v]=u; prevedge[v]=i;
						curflow[v]=min(curflow[u], e.cap-e.f);
					}
				}
			}
			if(prio[t]==INFCOST) break;
			FOR(i,0,n) pot[i]+=prio[i];
			tf df=min(curflow[t], INFFLOW-flow);
			flow+=df;
			for(int v=t; v!=s; v=prevnode[v]) {
				edge &e=g[prevnode[v]][prevedge[v]];
				e.f+=df; g[v][e.rev].f-=df;
				flowcost+=df*e.cost;
			}
		}
		return {flow,flowcost};
	}
};



int main() {
    int n, q;
    rii(n, q);
    vi up_b(n + 1, n), lo_b(n + 1, 1);

    MCF mcf(160);
    int s = 158, t = 159;

    FOR(i, 0, q) {
        int a, b, c, d;
        rii(a, b), rii(c, d);
        if (a == 1)
            FOR(i, b, c + 1) lo_b[i] = max(lo_b[i], d);
        else
            FOR(i, b, c + 1) up_b[i] = min(up_b[i], d);
    }

    FOR(i, 1, n + 1) mcf.add_edge(s, i, 1, 0);
    FOR(i, 1, n + 1) FOR(j, lo_b[i], up_b[i] + 1) mcf.add_edge(i, 50 + j, 1, 0);
    FOR(i, 1, n + 1) FOR(j, 1, n + 1) mcf.add_edge(50 + i, 100 + j, 1, 0);
    FOR(j, 1, n + 1) mcf.add_edge(100 + j, t, n, 2 * j - 1);

    auto [flow, cst] = mcf.get_flow(s, t);

    if (flow == n)
        printf("%lld\n", cst);
    else
        printf("-1\n");


    return 0;
}