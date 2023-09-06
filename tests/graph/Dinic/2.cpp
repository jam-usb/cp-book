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
#define ALL(s) s.begin(),s.end()
#define SZ(s) (int)s.size()
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x).size()

const int INF = 0x3f3f3f3f;
const ll LLINF = 1e18;
const int MAXN = 100; // CAMBIAR ESTE

// GJNM
typedef long long flow_t; // long long or int depending on the needs of the problem
struct Dinic{
	int nodes,src,dst;
	vi dist,q,work;
	struct edge {int to,rev;flow_t f,cap;};
	vector<vector<edge>> g;
	Dinic(int x):nodes(x),dist(x),q(x),work(x),g(x){}
	void add_edge(int s, int t, flow_t cap){
		g[s].pb((edge){t,sz(g[t]),0,cap});
		g[t].pb((edge){s,sz(g[s])-1,0,0});
	}
	bool dinic_bfs(){
		fill(all(dist),-1);dist[src]=0;
		int qt=0;q[qt++]=src;
		for(int qh=0;qh<qt;qh++){
			int u=q[qh];
			FOR(i,0,sz(g[u])){
				edge &e=g[u][i];int v=g[u][i].to;
				if(dist[v]<0&&e.f<e.cap)dist[v]=dist[u]+1,q[qt++]=v;
			}
		}
		return dist[dst]>=0;
	}
	flow_t dinic_dfs(int u, flow_t f){
		if(u==dst)return f;
		for(int &i=work[u];i<sz(g[u]);i++){
			edge &e=g[u][i];
			if(e.cap<=e.f)continue;
			int v=e.to;
			if(dist[v]==dist[u]+1){
				flow_t df=dinic_dfs(v,min(f,e.cap-e.f));
				if(df>0){e.f+=df;g[v][e.rev].f-=df;return df;}
			}
		}
		return 0;
	}
	flow_t max_flow(int _src, int _dst){
		src=_src;dst=_dst;
		flow_t result=0;
		while(dinic_bfs()){
			fill(all(work),0);
			while(flow_t delta=dinic_dfs(src,INF))result+=delta;
		}
		return result;
	}
};


vector<tuple<int, int, int>> div_cnt[MAXN];

int main() {
    int n, m; rii(n, m);
    int tot = 1;
    FOR(j, 0, n) {
        int a; ri(a);
        for (int i = 2; i * i <= a; i++) {
            if (a % i == 0) {
                int cnt = 0;
                while (a % i == 0) {
                    ++cnt;
                    a /= i;
                }
                div_cnt[j].pb({i, cnt, tot++});
            }
        }
        if (a > 1)
            div_cnt[j].pb({a, 1, tot++});
    }

    int s = 0, t = tot;
    Dinic mxf(tot + 1);

    FOR(i, 0, n) {
        for (auto [_, cap, ind] : div_cnt[i]) {
            if (i & 1)
                mxf.add_edge(ind, t, cap);
            else
                mxf.add_edge(s, ind, cap);
        }
    }

    FOR(__, 0, m) {
        int a, b; rii(a, b); --a, --b;
        if (a & 1)
            swap(a, b);

        int ai = 0, bi = 0;
        while (ai < SZ(div_cnt[a]) && bi < SZ(div_cnt[b])) {
            int ad = get<0>(div_cnt[a][ai]);
            int aind = get<2>(div_cnt[a][ai]);
            int bd = get<0>(div_cnt[b][bi]);
            int bind = get<2>(div_cnt[b][bi]);

            if (ad == bd) {
                mxf.add_edge(aind, bind, INF);
                ++ai;
                ++bi;
            }
            else if (ad < bd)
                ++ai;
            else
                ++bi;
        }
    }
    printf("%lld\n", mxf.max_flow(s, t));
    return 0;
}