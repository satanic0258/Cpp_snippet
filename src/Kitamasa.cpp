// Description: きたまさ法を用いてK項間漸化式の第N項目を計算する。O(K^2 logN)。

// きたまさ法を用いてK項間漸化式の第N項目を計算する。O(K^2 logN)。
// 第1引数 : A[n] = a[0] * A[n-k] + a[1] * A[n-k+1] + ... + a[k-1] * A[n-1]
// 第2引数 : A[0] = x[0], A[1] = x[1], ... , A[k-1] = x[k-1]
// 第3引数 : n
int Kitamasa(std::vector<int> a, std::vector<int> x, int n) {
	int k = a.size();
	std::vector<int> t(2 * k + 1);

	std::function<std::vector<int>(int)> rec = [&](int n) {
		std::vector<int> c(k);
		if (n < k) c[n] = 1;
		else {
			std::vector<int> b = rec(n / 2);
			std::fill(t.begin(), t.end(), 0);
			for (int i = 0; i < k; ++i) {
				for (int j = 0; j < k; ++j) {
					t[i + j + (n & 1)] += b[i] * b[j];
				}
			}
			for (int i = 2 * k - 1; i >= k; --i) {
				for (int j = 0; j < k; j++) {
					t[i - k + j] += a[j] * t[i];
				}
			}
			for (int i = 0; i < k; ++i) c[i] = t[i];
		}
		return c;
	};

	std::vector<int> c = rec(n);
	int ans = 0;
	for (int i = 0; i < x.size(); ++i) {
		ans += c[i] * x[i];
	}
	return ans;
}