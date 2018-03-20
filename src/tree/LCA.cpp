// Description: ダブリングを用いて2頂点におけるLCA(最近共通祖先)を求める。前計算O(NlogN)。クエリO(logN)。

// write [ LCA lca(g, root); ] when using this snippet.
class LCA {
private:
	const std::vector<std::vector<int>>& graph; // graph's list expression
	int root;
	int n; // the number of nodes
	int log2n; // = floor(log2(n)) + 1
	std::vector<std::vector<int>> parent; // parent[x][v] = a parent(above 2^x) of v (nonexistence -> -1)
	std::vector<int> depth; // the depth of each node

public:
	LCA(const std::vector<std::vector<int>>& graph, int root) :
		graph(graph), root(root), n(graph.size()),
		log2n(std::floor(std::log2(n) + 1)),
		parent(log2n, std::vector<int>(n, 0)), depth(n, 0)
	{
		init();
	}

	// Check the depth of each node(node "v" -> parent is "p", depth is "d")
	void dfs(int v, int p, int d) {
		std::stack<int> stack;
		stack.push(v);
		parent[0][v] = p;
		depth[v] = d;
		while (!stack.empty()) {
			int now = stack.top(); stack.pop();
			for (int i = 0; i < graph[now].size(); ++i) {
				int to = graph[now][i];
				if (to == parent[0][now]) continue;
				parent[0][to] = now;
				depth[to] = depth[now] + 1;
				stack.push(to); // Check each child of v
			}
		}
	}

	// Initialize
	void init() {
		// Initialize "parent[0]" and "depth"
		dfs(root, -1, 0);

		// Initialize "parent"
		for (int k = 0; k < log2n - 1; ++k) {
			for (int v = 0; v < n; ++v) {
				if (parent[k][v] < 0) { // If parent above 2^k of v is nonexistence
					parent[k + 1][v] = -1;
				}
				else {
					parent[k + 1][v] = parent[k][parent[k][v]];
				}
			}
		}
	}

	// Find LCA of (u, v)
	int lca(int u, int v) {
		// go up parent while depth of u and v is same
		if (depth[u] > depth[v]) std::swap(u, v);
		for (int k = 0; k < log2n; ++k) {
			if ((depth[v] - depth[u]) >> k & 1) {
				v = parent[k][v]; // go up to 2^k if k-th binary is 1
			}
		}

		if (u == v) return u; // this case is that v is in u's subtree

		// Find LCA by binary searching
		for (int k = log2n - 1; k >= 0; --k) {
			if (parent[k][u] != parent[k][v]) {
				u = parent[k][u];
				v = parent[k][v];
			}
		}
		return parent[0][u];
	}
};