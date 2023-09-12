/**
 * Description: Hungarian Algorithm for assignment problem (min or max cost in a perfect bipartite matching)
 * Time: O(n^3) for n==m | O(n^2*m) for rectangular problems, n<m
 */

typedef long double T;
typedef vector<T> vd;
const T INF = 1e100;  // for maximum set INF to 0, and negate costs
bool zero(T x) { return fabs(x) < 1e-9; }  // change to x==0, for ints/ll
struct Hungarian {
    int n;
    vector<vd> cs;
    vi L, R; // here are the matches
    Hungarian(int N, int M) : n(max(N, M)), cs(n, vd(n)), L(n), R(n) {
        FOR(x, 0, N) FOR(y, 0, M) cs[x][y] = INF;
    }
    void set(int x, int y, T c) { cs[x][y] = c; }
    T solve() {
        int mat = 0;
        vd ds(n), u(n), v(n);
        vi dad(n), sn(n);
        FOR(i, 0, n) u[i] = *min_element(all(cs[i]));
        FOR(j, 0, n) {
            v[j] = cs[0][j] - u[0];
            FOR(i, 1, n) v[j] = min(v[j], cs[i][j] - u[i]);
        }
        L = R = vi(n, -1);
        FOR(i, 0, n) FOR(j, 0, n)
            if (R[j] == -1 && zero(cs[i][j] - u[i] - v[j])) {
                L[i] = j;
                R[j] = i;
                mat++;
                break;
            }
        for (; mat < n; mat++) {
            int s = 0, j = 0, i;
            while (L[s] != -1) s++;
            fill(all(dad), -1);
            fill(all(sn), 0);
            FOR(k, 0, n) ds[k] = cs[s][k] - u[s] - v[k];
            for (;;) {
                j = -1;
                FOR(k, 0, n)
                    if (!sn[k] && (j == -1 || ds[k] < ds[j])) j = k;
                sn[j] = 1;
                i = R[j];
                if (i == -1) break;
                FOR(k, 0, n)
                    if (!sn[k]) {
                        auto new_ds = ds[j] + cs[i][k] - u[i] - v[k];
                        if (ds[k] > new_ds) {
                            ds[k] = new_ds;
                            dad[k] = j;
                        }
                    }
            }
            FOR(k, 0, n)
                if (k != j && sn[k]) {
                    auto w = ds[k] - ds[j];
                    v[k] += w;
                    u[R[k]] -= w;
                }
            u[s] += ds[j];
            while (dad[j] >= 0) {
                int d = dad[j];
                R[j] = R[d];
                L[R[j]] = j;
                j = d;
            }
            R[j] = s;
            L[s] = j;
        }
        T value = 0;
        FOR(i, 0, n) value += cs[i][L[i]];
        return value;
    }
};
