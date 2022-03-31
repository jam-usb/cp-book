/**
 * Author: bomba de tenedores
 * Description: Li Chao Tree
*/
#include <complex>

// Se cambia T dependiendo del caso
typedef ll T;
typedef complex<T> pt;

#define x real
#define y imag

T dot(pt v, pt w) { return (conj(v)*w).x(); }
T f(pt l, T x) { return dot(l, {x, 1}); }

// Maximum value a query can have
const int MAXQ = 2e5+5;

// Init en {0, INF}
pt LCT[4*MAXQ];
void add(pt nw, int id = 1, int l = 0, int r = MAXQ){
    int m = (l + r)>>1, L = id<<1, R = L|1;
    bool lef = f(nw, l) < f(LCT[id], l);
    bool mid = f(nw, m) < f(LCT[id], m);
    if(mid){
        swap(LCT[id], nw);
    }
    if(r - l == 1) return;
    if(lef != mid) add(nw, L, l, m);
    else add(nw, R, m, r);
}

// Retorna el minimo mx + b
// Para el maximo insertar {-m, -b} y hacer -get(x)
T get(int x, int id = 1, int l = 0, int r = MAXQ){
    int m = (l + r)>>1, L = id<<1, R = L|1;
    if(r - l == 1) return f(LCT[id], x);
    if(x < m) return min(f(LCT[id], x), get(x, L, l, m));
    return min(f(LCT[id], x), get(x, R, m, r));
}