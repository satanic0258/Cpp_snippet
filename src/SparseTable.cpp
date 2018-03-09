// Description: 静的配列に対してRMQを前計算O(NlogN)，クエリO(1)でこなす．

enum FUNC_SparseTable { MIN, MAX };
template<class T>
class SparseTable {
	size_t N;
	std::vector<T> a;
	std::vector<size_t> logTable;
	std::vector<std::vector<T>> table;
	std::function<T(T&, T&)> f;
public:
	SparseTable(const std::vector<T>& _a, FUNC_SparseTable func = MIN) : N(_a.size()), a(_a) {
		logTable.resize(N + 1, 0);
		for (size_t i = 2; i <= N; ++i) {
			logTable[i] = logTable[i >> 1] + 1;
		}

		switch (func) {
			case MIN: f = [](T& l, T& r) { return std::min(l, r); }; break;
			case MAX: f = [](T& l, T& r) { return std::max(l, r); }; break;
		}

		table.resize(logTable[N] + 1, std::vector<T>(N));
		for (size_t i = 0; i < N; ++i) table[0][i] = a[i];
		for (size_t k = 1; k <= logTable[N]; ++k) {
			for (size_t i = 0; i + (1 << k) <= N; ++i) {
				table[k][i] = f(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
			}
		}
	}
	// query in [l, r)
	inline T query(int l, int r) {
		int lg = logTable[r - l];
		return f(table[lg][l], table[lg][r - (1 << lg)]);
	}
};