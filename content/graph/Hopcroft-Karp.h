/**
 * Author: Bomba de tenedores
 * Description: Hopcroft-Karp
 * Time: $O(\sqrt{V}E)$
 */
 
/*
Problemas de mathing
* - Matching maximo: C(S,v)=INF; C(v,w)=INF; C(w,t)=1
* - Conjunto de aristas minimo que cubra los 2 conjundores del Grafo: MatchingMaximo y se completan lso nodos que quedaron solos
* - Minimo cubrimiento por nodos: Se busca corte minimo y los extremos  de los edges cortados son los nodos
* - Maximo conjunto independiente (conjunto de vertices que no se  conectan): Complemento de los nodos del problema 3 o lo que es lo  mismo #nodos - maxMatching
* - Como encontrar nodos del Minimum Vertex Cover (los del Maximum Independent Set son el complemento):
* - Give orientation to the edges, matched edges start from the right side of the graph to the left side, and free edges start from the left side of the graph to the right side.
* - Run DFS from unmatched nodes of the left side, in this traversal some nodes will become visited, others will stay unvisited.
* - The MVC nodes are the visited nodes from the right side, and unvisited nodes from the left side.
*/
// A from 1 to A
// B from A+1 to A+B < MAXN
vi G[MAXN]; // edges A->B  //clear G for several test cases
int A, B, match[MAXN], dist[MAXN];
bool bfs() {
	queue<int> q;
	FOR(i,1,A+1){
		if(match[i]==0){
			dist[i]=0;
			q.push(i);
		} else dist[i]=INF;
	}
	dist[0] = INF;
	while(!q.empty()) {
		int v = q.front(); q.pop();
		if(v!=0) {
			FOR(i,0,sz(G[v])){
				int u = G[v][i];
				if(dist[match[u]]==INF) {
					dist[match[u]] = dist[v] + 1;
					q.push(match[u]);
				}
			}
		}
	}
	return (dist[0]!=INF);
}
bool dfs(int v) {
	if(v!=0) {
		FOR(i,0,sz(G[v])){
			int u = G[v][i];
			if(dist[match[u]]==dist[v]+1) {
				if(dfs(match[u])) {
					match[u] = v;
					match[v] = u;
					return true;
				}
			}
		}
		dist[v] = INF;
		return false;
	}
	return true;
}
int HK(){
	ms(match, 0);
	int MBM = 0;
	while(bfs())
		FOR(i,1,A+1)
			if(match[i]==0 && dfs(i))
				MBM++;
	return MBM;
}
