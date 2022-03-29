/**
 * Author: ulimit
 * Description: Disjoint set union
 * Time: $O(\alpha(N))$
 */

int father[MAXN], siz[MAXN];
void makeSet(int n, int m){
	for (int i = n; i <= m; ++i){
		father[i] = -1;
		siz[i] = 0;
	}
}
int find(int x){
	if (father[x]==-1)  return x;
	return father[x] = find(father[x]);
}
void unio(int x, int y){ 
	if (siz[x] > siz[y]) 
		father[y] = x;
	else{
		father[x] = y;
		if ( siz[x] == siz[y] ) siz[y]++;
	}
}
