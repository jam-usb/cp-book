/**
 * Author: ulimit
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Time: O(N+M) 
 */

int t;
int low[MAXN], disc[MAXN];
bool vis[MAXN];
stack<int> st;

void initTarjan(){
	ms(low,-1); 
	ms(disc,-1);
}

void tarjan(int u){
	low[u] = disc[u] = t++;
	vis[u] = true;
	st.push(u);

	for(auto v : G[u]){
		if ( low[v] == -1 )
			tarjan(v);
		if ( vis[v] )
			low[u] = min(low[u], low[v]);
	}

	if ( low[u] == disc[u] ){
		while(1){ // Los que salgan de la pila en este ciclo son de la misma comp
			int v = st.top();
			st.pop();
			vis[v] = false;


			if ( u == v )
				break;
		}
	}
}
