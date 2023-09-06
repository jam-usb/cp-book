/**
 * Author: el vasito
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * Time: $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on CF-498C
 */

typedef int flow_t; // long long or int depending on the needs of the problem
struct Dinic{
	int nodes,src,dst;
	vi dist,q,work;
	struct edge {int to,rev;flow_type f,cap;};
	vector<vector<edge>> g;
	Dinic(int x):nodes(x),dist(x),q(x),work(x),g(x){}
	void add_edge(int s, int t, flow_type cap){
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
	flow_type dinic_dfs(int u, flow_type f){
		if(u==dst)return f;
		for(int &i=work[u];i<sz(g[u]);i++){
			edge &e=g[u][i];
			if(e.cap<=e.f)continue;
			int v=e.to;
			if(dist[v]==dist[u]+1){
				flow_type df=dinic_dfs(v,min(f,e.cap-e.f));
				if(df>0){e.f+=df;g[v][e.rev].f-=df;return df;}
			}
		}
		return 0;
	}
	flow_type max_flow(int _src, int _dst){
		src=_src;dst=_dst;
		flow_type result=0;
		while(dinic_bfs()){
			fill(all(work),0);
			while(flow_type delta=dinic_dfs(src,INF))result+=delta;
		}
		return result;
	}
};
