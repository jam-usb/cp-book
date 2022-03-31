/**
 * Author: bomba de tenedores
 * Description: Chinese remainder theorem
 */
// lowest common multiple of two integers (ll).
ll lcm(ll a, ll b){
    return a / __gcd(a, b) * b;
}

// Auxiliar struct for the return type of extended euclidean algorithm for gcd.
struct GCDtuple { ll x, y, d; };
// Extended euclidean algorithm for gcd. 
// Also return integers x,y of the bezout's identity (if gcd(a,b)=d then exist x and y such that ax+by=d)
GCDtuple extGCD(ll a, ll b){

    //if(a==0 && b==0) return {1,1,0};
    if (b == 0) return {1, 0, a};
    if (a == 0) return {0, 1, b};

    GCDtuple ret = extGCD(b, a % b);
    return {ret.y, ret.x - a / b * ret.y, ret.d};
}

int t; //number of congruences of the CRT system.
ll a[MAXN], n[MAXN], LCM; // array a of remainder mod moduli, and array n of modulis. LCM of modulis.

// Algorithm to solve a system of congruences with the Chinese Remainder Theorem.
// (is not needed the modulis to be pairwise coprime)
ll CRT(){

    ll ans = a[0];
    LCM = n[0];

    FOR(i,1,t){

        auto eg = extGCD(LCM, n[i]);
        int x1 = eg.x;
        int d = eg.d;

        if((a[i]-ans)%d!=0){ // No solution
            printf("no solution\n");
            return -1;
        }

        ans = (ans + (((x1*((a[i]-ans)/d))%(n[i]/d))*LCM)%(LCM/d*n[i]) + LCM/d*n[i] )%(LCM/d*n[i]);

        LCM = lcm(LCM,n[i]);
    }

    return ans;
}