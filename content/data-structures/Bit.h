/**
 * Author: Bomba de tenedores
 * Description: Bit data structure
 * Time: O(\log N) each function
 */
 
ll BIT[MAXN], LOGN = log2(MAXN)+1;
void updBIT(int p, ll val){ 
    p++;	
    for(; p < MAXN; p += p&-p) BIT[p] += val;
}

ll sumBIT(int p){
    p++;
    ll ret = 0;
    for(; p; p -= p&-p) 
    	ret += BIT[p];
    return ret;
}

// lower bound on prefix sum
int bit_search(int v){
	int sum = 0;
	int pos = 0;
	
	for(int i=LOGN; i>=0; i--){
		if(pos + (1 << i) < MAXN and sum + BIT[pos + (1 << i)] < v){
			sum += BIT[pos + (1 << i)];
			pos += (1 << i);
		}
	}

	return pos + 1; 
}
