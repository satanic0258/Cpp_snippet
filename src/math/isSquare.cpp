// Description: 平方数かどうかを判定する。非負整数のみ。O(1)。

// only non-negative integer (i.e. only n>=0)
bool isSquare(ll n) {
	struct Domain_Error {};
	if (n < 0) throw Domain_Error();
	ll d = (ll)std::sqrt(n) - 1;
	while (d*d < n) ++d;
	return d*d == n;
}