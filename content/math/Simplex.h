/**
 * Author: ulimit
 * Description: Simplex
 */
  
typedef double T; // long double, Rational, double + mod<P>...
const T EPS = 1e-8;

vector<int> X,Y;
vector<vector<T> > A;
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
    n=b.size();m=c.size();z=0.;
    X=vector<int>(m);Y=vector<int>(n);
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