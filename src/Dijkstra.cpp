// Description: ダイクストラ法を用いて単一始点最短経路を計算する。O(ElogV)。

struct Edge {
	int to, cost;
	Edge() {}
	Edge(int to, int cost) : to(to), cost(cost) {}
	bool operator<(const Edge& r) const {
		return cost < r.cost;
	}
};
std::vector<std::vector<Edge>> g($NODE_NUM$);
// 辺の追加

//
std::vector<int> dist($NODE_NUM$);
std::function<void(int)> Dijkstra = [&](int s) {
	using P = std::pair<int, int>;
	std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
	std::fill(dist.begin(), dist.end(), INFLL);
	dist[s] = 0;
	pq.push(P(0, s));
	while (!pq.empty()) {
		P p = pq.top(); pq.pop();
		int v = p.second;
		if (dist[v] < p.first) continue;
		for (int i = 0; i < g[v].size(); ++i) {
			Edge e = g[v][i];
			if (dist[e.to] > dist[v] + e.cost) {
				dist[e.to] = dist[v] + e.cost;
				pq.push(P(dist[e.to], e.to));
			}
		}
	}
};