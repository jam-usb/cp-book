/**
 * Author: bomba de tenedores
 * Description: Pollards Rho
 */

ll mult(ll a, ll b, ll mod){
    return (__int128)a * b % mod;
}
ll f(ll x, ll c, ll mod){
    return (mult(x, x, mod) + c) % mod;
}
ll rho(ll n){ // Works in O(n^(1/4) * log(n))
    ll x = 2, y = 2, g = 1;
    ll c = rand() % n + 1;
    while(g == 1){
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = __gcd(abs(x - y), n);
    }
    return g==n ? rho(n) : g;
}
map <ll, ll> fact;
void factRho(ll n){
    if(n == 1) return;
    if(RabinMiller(n)){
        fact[n]++;
        return;
    }
    ll factor = rho(n);
    factRho(factor);
    factRho(n/factor);
}
void factor(ll n){
    ll i = 2;
    while(n > 1 && i < 60){
        while(n % i == 0) fact[i]++, n /= i;
        i++;
    }
    factRho(n);
}