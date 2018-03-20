// Description: 木の重心分解を用いて木全体に対して再帰的にある処理を行う。O(NlogN)。

// ここから木の重心分解
// std::vector<std::vector<int>> g(n); という木が用意されている前提
std::vector<bool> used(n + 1, false);
std::vector<int> subtreeSize(n + 1, 0);

// 部分木のサイズを再帰的に計算する
// @param (v) スタートする頂点
// @param (par) vの親(部分木には含まれない)
// @return 部分木のサイズ
std::function<int(int, int)> calcSubtreeSize = [&](int v, int par) {
	int res = 1;
	for (const auto& to : g[v]) {
		if (to == par || used[to]) continue;
		res += calcSubtreeSize(to, v);
	}
	return subtreeSize[v] = res;
};

// 部分木の重心を再帰的に探す
// @param (v) スタートする頂点
// @param (par) vの親(部分木には含まれない)
// @param (size) 連結成分全体のサイズ(外から呼び出した時の部分木のサイズ)
// @return (残る部分木でサイズが最大のものの頂点数, 重心の番号)
std::function<std::pair<int, int>(int, int, int)> getCentroid = [&](int v, int par, int size) {
	std::pair<int, int> res = std::make_pair(INFINT, -1);
	// (s) vの部分木のサイズ
	// (m) vに隣接している頂点の部分木のうち最大サイズ(parより上も含む) 
	int s = 1, m = 0;
	for (const auto& to : g[v]) {
		if (to == par || used[to]) continue;
		res = std::min(res, getCentroid(to, v, size));
		m = std::max(m, subtreeSize[to]);
		s += subtreeSize[to];
	}
	m = std::max(m, size - s); // parより上も調べる
	res = std::min(res, std::make_pair(m, v));
	return res;
};
// ここまで木の重心分解

// ここから答えを求める
std::vector<int> ans(n);
std::function<void(int)> solve = [&](int v) {
	int s = calcSubtreeSize(v, -1);
	auto p = getCentroid(v, -1, s);
	used[p.second] = true;

	// 木に対する処理

	for (const auto& next : g[p.second]) {
		if (used[next]) continue;
		solve(next);
	}
};
solve(0);