/**
 * Author: bomba de tenedores
 * Description: Convex Hull Trick
*/

struct line{
    ll m,b;
};
vector <line> v;

double inters(line l1, line l2){
    return 1.0*(l1.b-l2.b)/(l2.m-l1.m);
}

//Se deben agregar las rectas en orden decreciente (Lower Hull (buscar min)) o creciente (Upper Hull) de m 
//Si se cambian los < por > en add y query se puede hacer al reves
void add(line l){
    int n=v.size();
    if(n<2) {v.pb(l); return;}
    if(inters(v[n-1],v[n-2]) < inters(l,v[n-2])) v.pb(l);
    else{
        v.pop_back();
        add(l);
    }
}

//Devuelve x que maximice (o minimice) m*x + b para alguna de las rectas (m,b)
ll query(ll x){
    int l = 0, r = v.size(); r--;
    assert(r != -1);
    while(l < r){
        int m = (l+r+1)>>1;
        if(inters(v[m],v[m-1]) > x) r = m-1;
        else l = m;
    }
    return v[l].m*x + v[l].b;
}