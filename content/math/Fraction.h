/**
 * Author: bomba de tenedores
 * Description: fraction template
 */

struct frac{
    ll p,q;
    frac(ll p=0, ll q=1):p(p),q(q) {norm();}
    ll gcd(ll a, ll b){return b ? gcd(b, a%b) : a; }
    void norm(){
        ll a = gcd(p,q);
        if(a) p/=a, q/=a;
        else q=1;
        if (q<0) q=-q, p=-p;}
    frac operator+(const frac& o){
        ll a = gcd(q,o.q);
        return frac(p*(o.q/a)+o.p*(q/a), q*(o.q/a));}
    frac operator-(const frac& o){
        ll a = gcd(q,o.q);
        return frac(p*(o.q/a)-o.p*(q/a), q*(o.q/a));}
    frac operator*(frac o){
        ll a = gcd(q,o.p), b = gcd(o.q,p);
        return frac((p/b)*(o.p/a), (q/a)*(o.q/b));}
    frac operator/(frac o){
        ll a = gcd(q,o.q), b = gcd(o.p,p);
        return frac((p/b)*(o.q/a),(q/a)*(o.p/b));}
    bool operator<(const frac &o) const{return p*o.q < o.p*q;}
    bool operator==(frac o){return p==o.p && q==o.q;}
};