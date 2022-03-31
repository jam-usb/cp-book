/**
 * Author: bomba de tenedores
 * Description: manacher for number of odd and even palindromes
 * Time: O(N)
 */
 
 vector<int> LCP(vector<int> sa, string s){ //sa = suffixArray
	int n = sa.size()-1, pos[n+2]={}, k = 0;
	FOR(i,0,sa.size()) pos[sa[i]] = i;
	vector<int> lcp(n+1,0); 
	FOR(i,0,n) if(pos[i]!=0){
		int pi = pos[i], j = sa[pi-1];
		while( k<n && s[i+k]==s[j+k]) k++;
		lcp[pi] = k;
		k = max(0,k-1);
	}
	return lcp;
}

