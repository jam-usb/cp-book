/**
 * Author: bomba de tenedores
 * Description: code for hld, also works for subtree.
 * [in[v], out[v]) corresponds to v's subtree
 * [in[nxt[v]], in[v]] path from v to last
 * vertex in ascending heavy path
 * Time: O(N)
 */
int t; // Timer
int in[MAXN], out[MAXN], nxt[MAXN], sz[MAXN];
 
void dfsSz(int v = 0, int p = -1){
    sz[v] = 1;
    for(auto &u : G[v]) if(u != p){
        dfsSz(u);
        sz[v] += sz[u];
        if(sz[u] > sz[G[v][0]]) swap(u, G[v][0]);
    }
}
void dfsHLD(int v = 0, int p = -1){
    in[v] = t++;
    for(auto u : G[v]) if(u != p){
        nxt[u] = (u == G[v][0] ? nxt[v] : u);
        dfsHLD(u);
    }
    out[v] = t;
}