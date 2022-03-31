/**
 * Author: bomba de tenedores
 * Description: Matrix operations
 */

// Matrix Inverse
bool inv(double **A, double **B, int N) {
    int jmax; double tmp;
    
    for (int i=0; i<N; i++) {
        jmax=i;
        
        for (int j=i+1; j<N; j++)
            if (abs(A[j][i])>abs(A[jmax][i])) jmax = j;
        
        for (int j=0; j<N; j++) {
            swap(A[i][j], A[jmax][j]);
            swap(B[i][j], B[jmax][j]);
        }
        
        if(abs(A[i][i])<EPS) return false;
        tmp=A[i][i];
        
        for (int j=0; j<N; j++) {
            A[i][j]/=tmp; 
            B[i][j]/=tmp;
        }
        for (int j=0; j<N; j++) {
            if(i==j) continue;
            tmp=A[j][i];
            for(int k=0; k<N; k++) {
                A[j][k]-=A[i][k]*tmp;
                B[j][k]-=B[i][k]*tmp;
            }
        }
    }
    return true;
}


double det(double *m[], int n) {
    if (n==2)
        return m[0][0]*m[1][1]-m[0][1]*m[1][0];
    double deter=0, M[n-1][n-1];
    double *m2[n-1];
    FOR(i, 0, n) {
        int sig=(i%2 ? -1 : 1);
        FOR(a, 1, n) {
            int k=0;
            FOR(b, 0, n) {
                if (b==i) continue;
                M[a-1][k++]=m[a][b];
            }
        }
        FOR(x, 0, n-1) m2[x]=M[x];
        deter = deter + m[0][i]*sig*det(m2, n-1);
    }
    return deter;
}

// Gauss Jordan para un vector especifico, sabiendo que el sistema
// tiene solucion unica con mas filas que columnas (mas ecuaciones 
// que variables)
void gauss(int A[][MAXM], int B[], int N, int M){
//  N es el numero de filas //  M es el numero de columnas
    int jmax, tmp;
    FOR(i, 0, M){
        jmax = i;
        FOR(j, i+1, N) if(A[j][i] > A[jmax][i]) jmax = j;
        FOR(j, 0, M) swap(A[i][j], A[jmax][j]);
        swap(B[i], B[jmax]);
        tmp = A[i][i];
        FOR(j, 0, M) A[i][j] = A[i][j]*inv[tmp]%MOD;
        B[i] = (B[i]*inv[tmp])%MOD;
        FOR(j, 0, N){
            if(i == j) continue;
            tmp = A[j][i];
            FOR(k, 0, M){
                A[j][k] -= A[i][k]*tmp;
                A[j][k] = (A[j][k]%MOD + MOD)%MOD;
            }
            B[j] -= B[i]*tmp;
            B[j] = (B[j]%MOD + MOD)%MOD;
        }
    }
}