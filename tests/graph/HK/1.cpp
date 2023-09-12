// https://codeforces.com/gym/101221 i 

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int das = 0;
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
const int MAXN = 100+5;

void fastIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}

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


vi G2[MAXN];
bool VISS[MAXN];
void dfss(int u) {
	VISS[u] = 1;
	for(int v : G2[u]) if(!VISS[v]) dfss(v);
}

int N,D;
int X[MAXN], Y[MAXN];
int SQ[MAXN][MAXN];
vi NODES;

int cross(int a, int b, int c) {
	return (X[b] - X[a]) * (Y[c] - Y[a]) - (Y[b] - Y[a]) * (X[c] - X[a]);
}

vi go(int u, int v) {
	NODES.clear();
	NODES.pb(u);
	NODES.pb(v);
	FOR(i,0,N) if (i != u && i != v && max(SQ[i][u], SQ[i][v]) <= SQ[u][v]) NODES.pb(i);

	vi lft, rgt;
	for(int i : NODES) {
		if (cross(u,v,i) <= 0) lft.pb(i);
		else rgt.pb(i);
	}

	A = sz(lft); B = sz(rgt);
	FOR(i,0,MAXN) G[i].clear();
	FOR(i,0,MAXN) G2[i].clear();
	FOR(i,0,MAXN) VISS[i] = 0;
	FOR(i,0,sz(lft)) FOR(j,0,sz(rgt)) {
		int l = lft[i], r = rgt[j];
		if (SQ[l][r] > SQ[u][v]) {
			G[1+i].pb(1+A+j);
		}
	}
	int x = HK();
	
	FOR(i,0,sz(lft)) FOR(j,0,sz(rgt)) {
		int l = lft[i], r = rgt[j];
		if (SQ[l][r] > SQ[u][v]) {
			if (match[1+i] == 1+A+j)
				G2[r].pb(l);
			else
				G2[l].pb(r);
		}
	}

	FOR(i,0,sz(lft)) if (!match[1+i]) dfss(lft[i]);

	vi ans;
	for(int l : lft) if (VISS[l]) ans.pb(l);
	for(int r : rgt) if (!VISS[r]) ans.pb(r);
	return ans;
}


int main(){
	rii(N,D);
	D = D * D;
	FOR(i,0,N) rii(X[i], Y[i]);
	FOR(i,0,N) FOR(j,0,N) SQ[i][j] = (X[i] - X[j]) * (X[i] - X[j]) + (Y[i] - Y[j]) * (Y[i] - Y[j]); 
	vi ans = {0};
	FOR(i,0,N) FOR(j,i+1,N) if (SQ[i][j] <= D){
		vi new_ans = go(i,j);
		if (sz(new_ans) > sz(ans)) ans = new_ans;
	}
	// ans = go(5,81);
	sort(all(ans));
	cout << sz(ans) << endl;
	for(int x : ans) cout << x + 1 << " ";
	cout << endl;

	return 0;
}