// Description: 素因数分解する。O(√N)。

std::vector<std::pair<ll, ll>> primeFact(ll n) {
	std::vector<std::pair<ll, ll>> result;
	for (ll i = 2; i*i <= n; ++i) {
		int divCount = 0;
		if (n%i == 0) {
			do {
				++divCount;
				n /= i;
			} while (n%i == 0);
			result.emplace_back(i, divCount);
		}
	}
	if (n != 1) result.emplace_back(n, 1);
	return result;
}