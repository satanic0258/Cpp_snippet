// Description: 木のオイラーツアーを構成する。O(N)。

struct EulerTour {
	std::vector<int> eulerTour;
	std::vector<int> begin, end; // [begin, end)
	int n, k;

	// 頂点vを根とする木gのオイラーツアー
	EulerTour(const std::vector<std::vector<int>>& g, int v) : n(g.size()), k(0) {
		begin.resize(n, 0);
		end.resize(n, 0);
		createEulerTour(g, v, -1);
	}

	// 頂点vを根とする木gのオイラーツアーを構成する
	void createEulerTour(const std::vector<std::vector<int>>& g, int v, int par) {
		begin[v] = k++;
		eulerTour.emplace_back(v);
		for (auto to : g[v]) {
			if (to == par) continue;
			createEulerTour(g, to, v);
			eulerTour.emplace_back(v);
			k++;
		}
		end[v] = k;
	}
};