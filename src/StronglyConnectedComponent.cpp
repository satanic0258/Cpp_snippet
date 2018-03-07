// Description: 有向グラフの強連結成分をつぶす。O(|V|+|E|)。

// use 'getDAG' after 'addEdge'.
// cmp : beforeV -> afterV ; v |-> cmp[v]
//    ... this is topo-order (use when DP).
struct StronglyConnectedComponent {
	int n;
	std::vector<std::vector<int>> g, rg;
	std::vector<bool> used;
	std::vector<int> vs; // postorder
	std::vector<int> cmp; // topo-order

	StronglyConnectedComponent(int n) :
		n(n), g(n), rg(n), used(n), cmp(n) {}

	int operator[](int id) {
		return cmp[id];
	}

	void addEdge(int from, int to) {
		g[from].emplace_back(to);
		rg[to].emplace_back(from);
	}

	void dfs(int v) {
		used[v] = true;
		for (size_t i = 0; i < g[v].size(); ++i) {
			if (!used[g[v][i]]) dfs(g[v][i]);
		}
		vs.emplace_back(v);
	}

	void rdfs(int v, int k) {
		used[v] = true;
		cmp[v] = k;
		for (size_t i = 0; i < rg[v].size(); ++i) {
			if (!used[rg[v][i]]) rdfs(rg[v][i], k);
		}
	}

	int scc() {
		used.assign(n, false);
		vs.clear();
		for (size_t v = 0; v < n; ++v) {
			if (!used[v]) dfs(v);
		}

		used.assign(n, false);
		int k = 0;
		for (signed i = vs.size() - 1; i >= 0; --i) {
			if (!used[vs[i]]) rdfs(vs[i], k++);
		}

		return k;
	}

	bool same(int u, int v) {
		return cmp[u] == cmp[v];
	}

	std::vector<std::vector<int>> getDAG() {
		int N = scc();
		std::vector<std::vector<int>> res(N);
		std::vector<std::set<int>> set(N);
		REP(i, n) {
			set[cmp[i]].insert(i);
		}
		REP(i, N) {
			std::set<int> out;
			for (const auto& v : set[i]) {
				for (const auto& to : g[v]) {
					out.insert(cmp[to]);
				}
			}
			for (const auto& to : out) {
				res[i].emplace_back(to);
			}
		}
		return res;
	}
};