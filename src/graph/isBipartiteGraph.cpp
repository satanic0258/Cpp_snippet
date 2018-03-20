// Description: グラフが無向グラフか判定する．O(N)．

// /*  g is     bipartite-graph : return 0/1 vector
// /*  g is NOT bipartite-graph : return empty vector
std::vector<int> isBipartiteGraph(const std::vector<std::vector<int>>& g) {
	int n = g.size();
	std::vector<int> res(n, -1);
	std::queue<int> que;
	que.push(0);
	res[0] = 0;
	while (!que.empty()) {
		int now = que.front(); que.pop();
		for (auto to : g[now]) {
			if (res[to] != -1) {
				if (res[now] == res[to]) {
					return std::vector<int>();
				}
			}
			else {
				res[to] = res[now] ^ 1;
				que.push(to);
			}
		}
	}
	return res;
}