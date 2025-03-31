/**
 * Author: not sure
 * Description: not needed
 */

void reduceMod2(vector<vi>& x) {
    int n = sz(x), m = sz(x[0]);
    int i = 0, j = 0, mod = 2;
    while (i < n && j < m) {
        int l = i;
        FOR(k, i + 1, n)if (x[k][j] > x[l][j])l = k;
        if (x[l][j] == 0) {j++; continue;}
        if (l != i) {swap(x[i], x[l]);}
        FOR(k, 0, n) {
            if (k == i)continue;
            for (int _l = m - 1; _l >= j; _l--)
                x[k][_l] = (x[k][_l] - x[k][j] * x[i][_l] + mod) & 1;
        }
        i++; j++;
    }
}