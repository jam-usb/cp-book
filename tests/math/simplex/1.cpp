// https://codeforces.com/group/gXivUSZQpn/contest/337359/problem/C

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <math.h>
#include <string>
#include <cstring>
#include <set>
#include <map>
#include <unordered_map>
#include <assert.h>
#include <array>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, pair<int, int>> piii;
typedef vector<int> vi;
typedef vector<pii> vii;

int dadsadasda;

#define ri(a) dadsadasda=scanf("%d", &a)
#define rii(a,b) dadsadasda=scanf("%d %d", &a, &b)
#define riii(a,b,c) dadsadasda=scanf("%d %d %d", &a, &b, &c)
#define rl(a) dadsadasda=scanf("%lld", &a)
#define rll(a,b) dadsadasda=scanf("%lld %lld", &a, &b)
#define FOR(i,n,m) for(int i=n; i<m; i++)
#define ROF(i,n,m) for(int i=n; i>m; i--)
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define F first
#define S second
#define all(s) s.begin(),s.end()
#define sz(s) (int)s.size()

const int INF = 0x3f3f3f3f;
const ll LLINF = 1e18;
const int MAXN = 1e5; // CAMBIAR ESTE

int N, P, Q;

/**
 * Author: ulimit
 * Description: Simplex
 */
  
typedef double T; // long double, Rational, double + mod<P>...
const T EPS = 1e-8;

vi X,Y;
vector<vector<T>> A;
vector<T> b,c;
T z;
int n,m;
void pivot(int x,int y){
    swap(X[y],Y[x]);
    b[x]/=A[x][y];
    FOR(i,0,m)if(i!=y)A[x][i]/=A[x][y];
    A[x][y]=1/A[x][y];
    FOR(i,0,n)if(i!=x&&abs(A[i][y])>EPS){
        b[i]-=A[i][y]*b[x];
        FOR(j,0,m)if(j!=y)A[i][j]-=A[i][y]*A[x][j];
        A[i][y]=-A[i][y]*A[x][y];
    }
    z+=c[y]*b[x];
    FOR(i,0,m)if(i!=y)c[i]-=c[y]*A[x][i];
    c[y]=-c[y]*A[x][y];
}
pair<T,vector<T> > simplex( // maximize c^T x s.t. Ax<=b, x>=0
        vector<vector<T> > _A, vector<T> _b, vector<T> _c){
    // returns pair (maximum value, solution vector)
    A=_A;b=_b;c=_c;
    n=sz(b);m=sz(c);z=0.;
    X=vi(m);Y=vi(n);
    FOR(i,0,m)X[i]=i;
    FOR(i,0,n)Y[i]=i+m;
    while(1){
        int x=-1,y=-1;
        double mn=-EPS;
        FOR(i,0,n)if(b[i]<mn)mn=b[i],x=i;
        if(x<0)break;
        FOR(i,0,m)if(A[x][i]<-EPS){y=i;break;}
        assert(y>=0); // no solution to Ax<=b
        pivot(x,y);
    }
    while(1){
        T mx=EPS;
        int x=-1,y=-1;
        FOR(i,0,m)if(c[i]>mx)mx=c[i],y=i;
        if(y<0)break;
        T mn=1e200;
        FOR(i,0,n)if(A[i][y]>EPS&&b[i]/A[i][y]<mn)mn=b[i]/A[i][y],x=i;
        assert(x>=0); // c^T x is unbounded
        pivot(x,y);
    }
    vector<T> r(m);
    FOR(i,0,n)if(Y[i]<m)r[Y[i]]=b[i];
    return {z,r};
}

int main() {
    riii(N, P, Q);

    vector<vector<T>> _A(2, vector<T>(N));
    FOR(i, 0, N) {
        dadsadasda = scanf("%lF %lF\n", &_A[0][i], &_A[1][i]);
        _A[0][i] *= -1;
        _A[1][i] *= -1;
    }
    vector<T> _b = { -1.0 * P, -1.0 * Q};
    vector<T> _c(N, -1);

    auto [ans, _] = simplex(_A, _b, _c);
    printf("%lF\n", -ans);

    return 0;
}