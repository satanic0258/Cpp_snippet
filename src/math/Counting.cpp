// Description: 数え上げライブラリ。

ll powMod(ll n, ll p, ll mod) {
	ll res = 1;
	while (p) {
		if (p & 1) (res *= n) %= mod;
		(n *= n) %= mod;
		p >>= 1;
	}
	return res;
}
ll invMod(ll n, ll mod) {
	return powMod(n, MOD - 2, MOD);
}

const signed FACT_MAX_N = 1000006;
signed fact[FACT_MAX_N];
signed factInv[FACT_MAX_N];
struct InitFact {
	InitFact() {
		fact[0] = 1;
		for (int i = 1; i < FACT_MAX_N; ++i) fact[i] = (long long)i * fact[i - 1] % MOD;
		factInv[FACT_MAX_N - 1] = powMod(fact[FACT_MAX_N - 1], MOD - 2, MOD);
		for (int i = FACT_MAX_N - 2; i >= 0; --i) factInv[i] = (long long)(i + 1) * factInv[i + 1] % MOD;
	}
} init_fact;

#if true // true if use MOD
/* n,r<=10^6, query O(1)*/
ll permutation(int n, int r) {
	if (r == 0) return 1;
	if (n < r) return 0;
	return (long long)fact[n] * factInv[n - r] % MOD;
}
ll combination(int n, int r) {
	if (r == 0) return 1;
	if (n < r) return 0;
	return (long long)fact[n] * factInv[n - r] % MOD * factInv[r] % MOD;
}
ll combinationWithRepetition(ll n, ll r) {
	return combination(n + r - 1, r);
}
/*n<=10^9, r<=10^5, query O(r)*/
/*ll combination(ll n, ll r, ll mod) {
	if (n < r) return 0;
	ll ans = 1;
	if (n < 2 * r) r = n - r;
	for (int i = 1; i <= r; ++i) {
		ans *= n - i + 1; ans %= mod;
		ans *= powMod(i, mod - 2, mod); ans %= mod;
	}
	return ans;
}
ll permutation(int n, int r, int mod) {
	return combination(n, r, mod) * fact[r] % MOD;
}*/
#else // unuse MOD
const signed COMB_MAX_N = 67; // <- max : 67
long long comb[COMB_MAX_N][COMB_MAX_N];
struct InitComb {
	InitComb() {
		for (int i = 0; i < COMB_MAX_N; ++i) {
			for (int j = 0; j <= i; ++j) {
				if (j == 0 || j == i) comb[i][j] = 1;
				else comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
			}
		}
	}
} init_comb;
#endif