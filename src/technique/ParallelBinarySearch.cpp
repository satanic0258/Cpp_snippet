// Description: 並列二分探索テンプレ．

// int m = (にぶたん範囲の最大値);
// int Q = (クエリの個数)

int M = 1; // 配列toの幅
while (M < m) M *= 2;
std::vector<std::vector<int>> from(1), to;
REP(i, Q) {
	from[0].emplace_back(i);
}
while (M > 1) {
	M /= 2;
	int med = M;
	int p = 0;
	to.resize(from.size() * 2);
	REP(si, from.size()) {
		while (p < m && p < med) {
			// ある時刻ごとに行う操作
			++p;
		}
		for(auto& i : from[si]) {
			if (/* にぶたんの条件 */) to[si * 2 + 0].emplace_back(i);
			/*              */ else to[si * 2 + 1].emplace_back(i);
		}
		med += M * 2;
	}
	from = decltype(from)();
	std::swap(from, to);
}
std::vector<int> ans(Q);
REP(si, from.size()) {
	for (auto& i : from[si]) {
		ans[i] = si + 1;
	}
}