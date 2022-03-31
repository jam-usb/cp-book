/**
 * Author: bomba de tenedores
 * Description: varias func matematicas
 */

//----------------NUMEROS DE BELL------
//
ll BELL[];
ll bell(int n){
    if(BELL[n]!=-1)
        return BELL[n];
    ll b =0;
    for(int k=0; k<n; k++)
        b += (COMB(n-1,k) * bell(k);
        //b = (b+(COMB(n-1,k) * bell(k))%MOD)%MOD;
    return BELL[n] = b;
}
ms(BELL,-1)
//-------Permutaciones de Multiconjunto------
//k es el vector de ocurrencias de cada elemento
//{a,a,a,b,c,c} -> k = [3,1,2]
ll mcomb(vi k){
    ll r = 1;
    ll s=0;
    for(int i=0; i<k.size(); i++){
        s+=k[i];
        r*= comb(s,k[i]);
    }
    return r;
}
//------- Recurrencias --------------
#define MN 2 //matriz MNxMN
typedef vector<ll>  vll;
typedef vector<vll>  MAT;
MAT operator*(MAT &a, MAT &b) {
    MAT res(MN, vll(MN));
    FOR(i,0,MN) FOR(j,0,MN) FOR(k,0,MN)
        res[i][j] = (res[i][j] + (a[i][k] * b[k][j]) % MOD) % MOD;
        //res[i][j] = res[i][j] + a[i][k] * b[k][j];
    return res;
}
MAT pot(MAT b, ll e){
    if(e==1) return b;
    if(e==2) return b*b;
    MAT r = pot(pot(b,e/2),2);
    if(e&1) return b*r;
    return r;
}
ll fib(ll n){
    if(n==0)
        return 0;
    else if(n==2 || n==1)
        return 1;
    MAT F(MN, vll(MN,1)); F[1][1]=0;
    return pot(F,n-1)[0][0];
}