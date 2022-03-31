/**
 * Author: bomba de tenedores
 * Description: Sieve
 */

// Init p[i] = 0, p[0] = p[1] = 0 BE CAREFUL!
void fillSieve(int p[]){
    for(ll i = 4; i < MAXN; i += 2) p[i] = 2;
    for(ll i = 3; i*i < MAXN; i += 2) if(!p[i])
        for(ll j = i*i; j < MAXN; j += 2*i) p[j] = i;
}