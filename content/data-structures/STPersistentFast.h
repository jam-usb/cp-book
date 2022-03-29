/**
 * Author: el vasito
 * Description: Persistent segment tree data structure (and Implicit) 
 * implemented with a vector
 * All the ranges are [a,b)
 * Time: O(\log N) each function
 */

#define oper2(st, L, R, ks) ((L[ks] == -1 ? 0 : st[L[ks]]) + (R[ks] == -1 ? 0 : st[R[ks]]))
#define oper(a, b) (a+b)
#define NEUT 0
#define INF 1000000007
struct STree { // persistent segment tree for sum over integers
	vector<int> st, L, R; int n,sz,rt;
	STree(int n): st(1,NEUT),L(1,-1),R(1,-1),n(n),rt(0),sz(1){}
	STree(){}
	int new_node(){
		int ids=SZ(st);
		st.pb(NEUT);L.pb(-1);R.pb(-1);
		return ids;
	}
	int upd(int id, int l, int r, int p, int v){
		int ids = (id == -1 ? new_node() : id);
		if(l+1==r){st[ids]+=v;return ids;}
		int m=(l+r)>>1,ps;
		if(p<m)ps=upd(L[ids],l,m,p,v),L[ids]=ps;
		else ps=upd(R[ids],m,r,p,v),R[ids]=ps;
		st[ids]=oper2(st, L, R, ids);
		return ids;
	}
	int query(int id, int l, int r, int a, int b){
		if(r<=a||b<=l||id==-1)return NEUT;
		if(a<=l&&r<=b)return st[id];
		int m=(l+r)>>1;
		return oper(query(L[id],l,m,a,b),query(R[id],m,r,a,b));
	}
	int upd(int p, int v){return rt=upd(rt,0,n,p,v);} // update on last root
	int query(int a, int b){return query(rt,0,n,max(0,a),min(b,INF));}; // sin pasarle la raiz
	//int query(int idRoot,int a, int b){return query(idRoot,0,n,a,b);};
	//int upd(int idRoot, int p, int v){return rt=upd(idRoot,0,n,p,v);}
};
