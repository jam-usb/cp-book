/**
 * Author: Bomba de tenedores
 * Description: Tarjan for Biconnected components
 * Time: O(V+E)
 */

vector<edge> G[MAXN], E;
int N;

vector<vi> BCC;
vi bridges, a_pts;

stack<int> stk;
int td[MAXN], low[MAXN];
void tarj(int v, int p){
	low[v] = td[v];
	bool is_a_pt = false;
	FOR(i,0,G[v].size()){
		int u=G[v][i].to, id=G[v][i].id;
		if(u==p || td[u] > td[v]) continue;
		stk.push(id);
		if(td[u]==-1){
			td[u] = td[v]+1;
			tarj(u,v);
			low[v] = min(low[v],low[u]);
			if(low[u] >= td[v]){ //v is an articulation point
				is_a_pt = true;
				int e=-1, x=BCC.size();
				BCC.pb(vi());
				while(e!=id){
					e=stk.top(); stk.pop();
					BCC[x].pb(e);
				}
			}
			if(low[u]==td[u]) //v - u is a bridge
				bridges.pb(id);
		}else low[v] = min(low[v],td[u]);
	}
	//non-root nodes
	if(td[v]!=0 && is_a_pt) a_pts.pb(v);
}

void findBCCs(){
	BCC.clear(), bridges.clear(), a_pts.clear();
	ms(td,-1);
	stk = stack<int>();
	FOR(v,0,N) if(td[v]==-1){
		td[v] = 0, tarj(v,-1);
		int cnt = 0;
		FOR(i,0,G[v].size() && cnt<2)
			if(td[G[v][i].to]==1) cnt++;
		if(cnt > 1) a_pts.pb(v);
	}
}
