/**
 * Author: Bomba de tenedores
 * Description: Longest Common Ancestor
 * Time: O(log(V))
 */

int H[MAXN];
int anc[MAXN][MAXLOG]; // init -1
void dfs_pre_LCA(int v, int p = -1){
	anc[v][0] = p;
	if(p != -1) H[v] = H[p] + 1;
	else H[v]=0;
	FOR(i,1,MAXLOG) if(anc[v][i-1] != -1)
		anc[v][i] = anc[anc[v][i-1]][i-1];
	FOR(i,0,G[v].size()){
		int u=G[v][i];
		if(p != u) dfs_pre_LCA(u,v);
	}
}

//Query:
int LCA(int u,int v){
	if(H[v] < H[u]) swap(v,u);
	FOR(i,MAXLOG-1,-1)
		if(anc[v][i] != -1 && H[anc[v][i]] >= H[u])
			v = anc[v][i];
	if(v == u) return v;
	FOR(i,MAXLOG-1,-1)
		if(anc[v][i] != anc[u][i])
			v = anc[v][i], u = anc[u][i];
	return anc[v][0];
}
