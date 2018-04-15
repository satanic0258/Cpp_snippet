// Description: 木の直径パスを取得する．O(N)．

std::vector<int> getDiameterPath(const std::vector<std::vector<int>>& g) {
	size_t n = g.size();

	std::vector<int> depth(n);
	int maxDepth = 0, farthest = -1;
	std::function<void(int, int)> getDepth = [&](int v, int par) {
		if (par == -1) {
			for (size_t i = 0; i < n; ++i) depth[i] = n;
			depth[v] = 0; maxDepth = 0, farthest = v;
		}
		for (auto&& to : g[v]) if (to != par) {
			depth[to] = depth[v] + 1;
			if (maxDepth < depth[to]) {
				maxDepth = depth[farthest = to];
			}
			getDepth(to, v);
		}
	};
	getDepth(0, -1);
	getDepth(farthest, -1);

	// Restore the diameter path
	std::vector<int> res(maxDepth + 1);
	size_t now = farthest;
	while (depth[now] != 0) {
		res[depth[now]] = now;
		for (auto&& to : g[now]) if (depth[to] + 1 == depth[now]) {
			now = to; break;
		}
	}
	res[depth[now]] = now;
	return res;
}