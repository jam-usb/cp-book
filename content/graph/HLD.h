/**
 * Author: bomba de tenedores
 * Description: code for hld, also works for subtree.
 * [in[v], out[v]) corresponds to v's subtree
 * [in[nxt[v]], in[v]] path from v to last
 * vertex in ascending heavy path
 * Time: O(N)
 */
int T; // Timer
int IN[MAXN], OUT[MAXN], NXT[MAXN], SZ[MAXN], F[MAXN], H[MAXN];
void dfsSz(int v = 0, int p = -1) {
    SZ[v] = 1;
    if (p != -1) H[v] = H[p] + 1;
    for (auto &u : G[v]) if (u != p) {
            dfsSz(u, v);
            SZ[v] += SZ[u];
            if (SZ[u] > SZ[G[v][0]] || G[v][0] == p) swap(u, G[v][0]);
        }
}
void dfsHLD(int v = 0, int p = -1) {
    IN[v] = T++;
    F[v] = p;
    for (auto u : G[v]) if (u != p) {
            NXT[u] = (u == G[v][0] ? NXT[v] : u);
            dfsHLD(u, v);
        }
    OUT[v] = T;
}