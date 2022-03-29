/**
 * Author: el vasito
 * Description: Suffix array in O( n log(n) ) 
 * Time: O(N*logN)
 */
 
#define RB(x) (x<n?r[x]:0)
void csort(vector<int>& sa, vector<int>& r, int k){
	int n=sa.size();
	vector<int> f(max(255,n),0),t(n);
	FOR(i,0,n)f[RB(i+k)]++;
	int sum=0;
	FOR(i,0,max(255,n))f[i]=(sum+=f[i])-f[i];
	FOR(i,0,n)t[f[RB(sa[i]+k)]++]=sa[i];
	sa=t;
}

vector<int> SuffixArray(string& s){ // O(n logn)
	int n=s.size(),rank;
	vector<int> sa(n),r(n),t(n);
	FOR(i,0,n)sa[i]=i,r[i]=s[i];
	for(int k=1;k<n;k*=2){
		csort(sa,r,k);csort(sa,r,0);
		t[sa[0]]=rank=0;
		FOR(i,1,n){
			if(r[sa[i]]!=r[sa[i-1]]||RB(sa[i]+k)!=RB(sa[i-1]+k))rank++;
			t[sa[i]]=rank;
		}
		r=t;
		if(r[sa[n-1]]==n-1)break;
	}
	return sa;
}
