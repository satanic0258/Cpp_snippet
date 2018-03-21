class PrimalDual {
    const int INF = (1LL << 31) - 1;
    struct Edge { int to, cap, cost, rev; };
 
    int N;
    std::vector<std::vector<Edge>> g;
    std::vector<int> h, dist, preV, preE;
 
public:
    PrimalDual(int n) : N(n), g(n), h(n), dist(n), preV(n, -1), preE(n, -1) {}
 
    // fromからtoへの辺(容量cap, コストcost)を張る
    void addEdge(int from, int to, int cap, int cost) {
        g[from].emplace_back(Edge{ to, cap, cost, (int)g[to].size() });
        g[to].emplace_back(Edge{ from, 0, -cost, (int)g[from].size() - 1 });
    }
 
    // sからtに流量fの最小費用流を求める (流せなければ-1)
    int minCostFlow(int s, int t, int f) {
        int res = 0;
        h.assign(N, 0);
        using P = std::pair<int, int>;
        while (f > 0) {
            std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
            dist.assign(N, INF);
            dist[s] = 0;
            pq.push(P(0, s));
            while (!pq.empty()) {
                P p = pq.top(); pq.pop();
                int v = p.second;
                if (dist[v] < p.first) continue;
                for (int i = 0; i < g[v].size(); ++i) {
                    Edge& e = g[v][i];
                    if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                        dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                        preV[e.to] = v;
                        preE[e.to] = i;
                        pq.push(P(dist[e.to], e.to));
                    }
                }
            }
            if (dist[t] == INF) return -1;
            for (int v = 0; v < N; ++v) h[v] += dist[v];
 
            // s-t間の最短経路に流す
            int d = f;
            for (int v = t; v != s; v = preV[v]) {
                d = std::min(d, g[preV[v]][preE[v]].cap);
            }
            f -= d;
            res += d * h[t];
            for (int v = t; v != s; v = preV[v]) {
                Edge& e = g[preV[v]][preE[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }
        return res;
    }
};