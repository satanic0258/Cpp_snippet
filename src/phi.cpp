// Description: オイラーのトーシェント関数を計算する。O(√n)。

int phi(int n) { // O(Sqrt(n))
	int res = n;
	for (int i = 2; i * i <= n; ++i) {
		if (n%i == 0) {
			res /= i;
			res *= i - 1;
		}
		while (n%i == 0) n /= i;
	}
	if (n != 1) {
		res /= n;
		res *= n - 1;
	}
	return res;
}