// Description: 素数かどうか判定する。O(√N)。

bool isPrime(ll n) {
	if (n < 2) return false;
	for (ll i = 2; i * i <= n; ++i) {
		if (n % i == 0) return false;
	}
	return true;
}