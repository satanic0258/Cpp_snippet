// Description: mod逆元を求める．初めO(log(mod))．

ll powMod(ll n, ll p, ll mod) {
	ll res = 1;
	while (p) {
		if (p & 1) (res *= n) %= mod;
		(n *= n) %= mod;
		p >>= 1;
	}
	return res;
}
std::map<int, int> inv;
ll invMod(ll n, ll mod) {
	if (inv.count(n)) return inv[n];
	return inv[n] = powMod(n, mod - 2, mod);
}