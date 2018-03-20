// Description: エラトステネスの篩を用いてN以下の素数を列挙する。O(logN)。

std::vector<int> eratosthenes(int n) {
	std::vector<bool> num(n, true);
	std::vector<int> prime;
	num[0] = false;
	for (int i = 0; i*i < n; ++i) {
		if (num[i]) {
			for (int j = 2; (i + 1)*j <= n; ++j) {
				num[(i + 1)*j - 1] = false;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		if (num[i]) {
			prime.push_back(i + 1);
		}
	}
	return prime;
}