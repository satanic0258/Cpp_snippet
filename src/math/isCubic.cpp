// Description: 立法数かどうかを判定する。非負整数のみ。O(1)。

// only non-negative integer (i.e. only n>=0)
bool isCubic(ll n) {
	struct Domain_Error {};
	if (n < 0) throw Domain_Error();
	ll d = (ll)std::pow(n, 1.0 / 3) - 1;
	while (d*d*d < n) ++d;
	return d*d*d == n;
}