// https://codeforces.com/gym/103855/problem/G

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

int dasdas;

#define FOR(i,n,m) for(int i = n; i < (int)m; i++)
#define ROF(i,n,m) for(int i = n; i > (int)m; i--)
#define ms(obj,val) memset(obj,val,sizeof(obj))
#define ri(a) dasdas=scanf("%d", &a)
#define rii(a,b) ri(a), ri(b)
#define lri(a) dasdas=scanf("%lld", &a)
#define lrii(a,b) lri(a), lri(b)
#define all(x) x.begin(),x.end()
#define sz(x) (int)(x).size()
#define pb push_back
#define S second
#define F first

const int INF = 0x3f3f3f3f;
const ll INFLL = 1e18;
const int MAXN = 3e5+5;

void fastIO() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}


const ll mod = (119 << 23) + 1, root = 62; // = 998244353
ll binpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<ll> vl;
void ntt(vl &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, binpow(root, mod >> s)};
		FOR(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	vi rev(n);
	FOR(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	FOR(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) FOR(j,0,k) {
			ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
			a[i + j + k] = ai - z + (z > ai ? mod : 0);
			ai += (ai + z >= mod ? z - mod : z);
		}
}
vl conv(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
	int inv = binpow(n, mod - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	FOR(i,0,n) out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}

int N;
char S[MAXN];
int A[MAXN];
ll SM[MAXN];

ll F[MAXN], IF[MAXN];
void pre() {
	F[0] = 1;
	FOR(i,1,N+1) F[i] = (F[i-1] * i) % mod;
	IF[N] = binpow(F[N], mod-2);
	for(int i = N-1; i >= 0; --i) IF[i] = (IF[i+1] * (i+1)) % mod;
	FOR(i,0,N+1) {
		assert( (F[i] * IF[i] % mod) == 1 );
	}
}
ll f(int x) {
	return (((F[N] * 2 % mod) * F[x-2] % mod) * IF[x+1] % mod);
}


ll solve() {
	SM[0] = (S[0] == 'B' ? A[0] % mod : 0);
	FOR(i,1,N) SM[i] = (SM[i-1] + (S[i] == 'B' ? A[i] % mod : 0)) % mod;
	int sz = 1;
	while(sz <= N) sz <<= 1;
	sz <<= 1;

	vl a(sz), b(sz);
	FOR(i,0,N) a[i] = (S[i] == 'W') * SM[i];
	FOR(i,0,N) b[N-i-1] = (S[i] == 'W');
	auto r = conv(a, b); 

	FOR(i,0,N) a[i] = (S[i] == 'W') ;
	FOR(i,0,N) b[N-i-1] = (S[i] == 'W') * SM[i];
	auto r2 = conv(a,b);

	ll ans = 0;
	FOR(i,2,N) {
		ans = (ans + r[N-1+i] * f(i) - r2[N-1+i] * f(i)) % mod;
	}
	ans = (ans + mod) % mod;
	return ans;
}


int main(){
	ri(N);
	pre();
	dasdas=scanf("%s\n", S);
	FOR(i,0,N) ri(A[i]);
	ll ans = solve();
	FOR(i,0,N) S[i] = (S[i] == 'W' ? 'B' : 'W');
	
	ans = (ans + solve()) % mod;
	cout << ans << endl;

	return 0;
}
