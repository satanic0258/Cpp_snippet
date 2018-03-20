// Description: 動的計画法を用いて最長増加部分列の長さを計算する。O(NlogN)。

int LIS(const std::vector<int>& a) {
	int n = a.size();
	std::vector<int> dp(n, INFINT);
	for (int i = 0; i < n; ++i) {
		*std::lower_bound(dp.begin(), dp.end(), a[i]) = a[i];
	}
	return std::distance(dp.begin(), std::lower_bound(dp.begin(), dp.end(), INFINT));
}