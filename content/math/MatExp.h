/**
 * Author: jesuswr
 * Description: super simple matrix exp template
 * Time: O(N^3 log(e))
 */
int N_STATES;
typedef long long T;
struct Matrix {
    vector<vector<T>> mat;
    Matrix(T val=0) {
        mat.resize(N_STATES, vector<T>(N_STATES, val));
    }
    Matrix operator*(Matrix &other) {
        Matrix ret(0);
        FOR(i, 0, N_STATES) FOR(k, 0, N_STATES) FOR(j, 0, N_STATES) {
            ret.mat[i][j] += mat[i][k] * other.mat[k][j];
        }
        return ret;
    }
};

Matrix bin_exp(Matrix b, ll e) {
    Matrix prod(0);
    FOR(i, 0, N_STATES) {
        prod.mat[i][i] = 1;
    }
    while (e > 0) {
        if (e & 1)
            prod = prod * b;
        b = b * b;
        e >>= 1;
    }
    return prod;
}