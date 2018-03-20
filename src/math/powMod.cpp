// Description: フェルマーの小定理を用いてn**p % modを計算する。O(log(p))。

ll powMod(ll n, ll p, ll mod) {
	ll res = 1;
	while (p) {
		if (p & 1) (res *= n) %= mod;
		(n *= n) %= mod;
		p >>= 1;
	}
	return res;
}