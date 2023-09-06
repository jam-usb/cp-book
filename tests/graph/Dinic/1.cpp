// https://codeforces.com/gym/101208 C 

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
const int MAXN = 25000+5;

void fastIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}

typedef int flow_t;
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



int N, M, C;
vii G[MAXN];
int DST[MAXN];

void dijkstra(int u) {
	FOR(i,0,N) DST[i] = 1e8;
	priority_queue< ii > pq;
	pq.push({0,u});
	DST[u] = 0;
	while(!pq.empty()) {
		auto [cst, u] = pq.top(); pq.pop();
		cst = -cst;
		if (cst > DST[u]) continue;
		for(auto [v,w] : G[u]) {
			int n_cst = cst + w;
			if (DST[v] > n_cst) {
				DST[v] = n_cst;
				pq.push({-DST[v], v});
			}
		}
	}
}

int go(const vi &roots) {
	if (sz(roots) == 1) return 1;
	Dinic cdlm(N+2);
	FOR(u,0,N) {
		for(auto [v,w] : G[u]) {
			if (DST[u] == DST[v] + w) cdlm.add_edge(u, v, 1);
		}
	}
	for(int x : roots) cdlm.add_edge(N, x, 1);
	cdlm.add_edge(0, N+1, MAXN);
	return cdlm.max_flow(N,N+1);
}

int main(){
	rii(N,M), ri(C);
	FOR(_,0,M) {
		int u, v, w; rii(u,v), ri(w); --u; --v;
		G[u].pb({v,w});
		G[v].pb({u,w});
	}
	dijkstra(0);
	vii dists;
	FOR(i,0,C) {
		int x; ri(x); --x;
		dists.pb({DST[x],x});
	}
	sort(all(dists));
	int l = 0, r = -69;
	int ans = 0;
	while(l < C) {
		r = l;
		vi roots;
		while(r < C && dists[l].F == dists[r].F) {
			roots.pb(dists[r].S);
			r += 1;
		}
		ans += go(roots);
		l = r;
	} 
	cout << ans << endl;
	return 0;
}
