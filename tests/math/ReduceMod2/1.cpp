// https://codeforces.com/group/gXivUSZQpn/contest/337359/problem/A

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
#define ALL(s) s.begin(),s.end()
#define sz(s) (int)s.size()

const int INF = 0x3f3f3f3f;
const ll LLINF = 1e18;
const int MAXN = 1e5; // CAMBIAR ESTE

bool SIEVE[600];
vi primes;
void pre() {
    for (int i  = 2; i < 600; ++i) {
        if (SIEVE[i])
            continue;
        primes.pb(i);
        int j = i + i;
        while (j < 600) {
            SIEVE[j] = 1;
            j += i;
        }
    }
}

int T, N;
int A[110];

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
void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    freopen("rsa.in", "r", stdin);
    freopen("rsa.out", "w", stdout);
    pre();
    rii(T, N);
    FOR(i, 0, N) ri(A[i]);

    vector<vi> x(T, vi(N + 1, 0));

    FOR(i, 0, N) FOR(j, 0, T) {
        while (A[i] % primes[j] == 0) {
            x[j][i]++;
            A[i] /= primes[j];
        }
        x[j][i] &= 1;
    }

    reduceMod2(x);

    int piv = 0;
    FOR(i, 0, N) {
        int cnt = 0;
        int ind;
        FOR(j, 0, T) if (x[j][i]) {
            cnt++;
            ind = j;
        }
        if (cnt == 1) {
            bool good = true;
            FOR(j, 0, i) if (x[ind][j]) {
                good = false;
            }
            piv += good;
        }
    }

    __int128 ans = 1;
    FOR(_, 0, N - piv) ans = ans * 2;
    ans = ans - 1;
    print(ans);
    return 0;
}