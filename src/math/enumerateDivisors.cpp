// Description: ある正整数Nの約数を列挙する。O(Sqrt(N))。

std::vector<int> enumerateDivisors(ll n) {
	std::set<int> set;
	for (int i = 1; i*i <= n; ++i) {
		if (n%i) continue;
		set.insert(i);
		set.insert(n / i);
	}
	std::vector<int> res(set.size());
	int p = 0;
	for (const auto& x : set) {
		res[p++] = x;
	}
	return res;
}