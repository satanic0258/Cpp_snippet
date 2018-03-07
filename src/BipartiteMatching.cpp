// Description: 二部マッチングを求める．O(|V||E|)．

// ## add_edge -> solve
struct BipartiteMatching {
	int V;
	std::vector<std::vector<int>> g;
	std::vector<int> match; // ## (i, match[i]) is matching pair
	std::vector<bool> used;

	BipartiteMatching(int v) : V(v) {
		g.resize(V);
		match.resize(V, -1);
		used.resize(V, false);
	}

	void add_edge(int u, int v) {
		g[u].emplace_back(v);
		g[v].emplace_back(u);
	}

	bool dfs(int v) {
		used[v] = true;
		for (auto& to : g[v]) {
			int u = match[to];
			if (u < 0 || (!used[u] && dfs(u))) {
				match[v] = to;
				match[to] = v;
				return true;
			}
		}
		return false;
	}

	int solve() {
		match.assign(V, -1);
		int res = 0;
		for (int v = 0; v < V; ++v) {
			if (match[v] < 0) {
				used.assign(V, false);
				if (dfs(v)) ++res;
			}
		}
		return res;
	}
};