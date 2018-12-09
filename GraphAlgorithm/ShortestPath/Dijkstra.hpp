#include <bits/stdc++.h>

using namespace std;

// Graph template
template <class... Args> struct Edge {
  int from, to;
  tuple<Args...> values;
  Edge(int from, int to, Args... values)
      : from(from), to(to), values(values...) {}
};
template <class E> auto operator<(const E &e, const E &f) {
  return e.values > f.values;
}

template <class... Args> class Graph {
  using Edges = vector<Edge<Args...>>;
  vector<Edges> graph_;

public:
  Graph(int n) : graph_(n) {}
  size_t size() { return graph_.size(); };
  size_t size() const { return graph_.size(); };
  auto &operator[](unsigned int x) { return graph_[x]; }
  const auto &operator[](unsigned int x) const { return graph_[x]; }
  void AddEdge(int s, int t, Args... v) { graph_[s].emplace_back(s, t, v...); }
};

constexpr long long INF64 = 1e18;

using Weight = long long;

template <class G> auto Dijkstra(const G &g, int s) {
  const int n = (int)g.size();
  vector<Weight> dist(n, INF64); //各点における始点sからの距離が入る
  vector<int> prev(n, -1);       //各点における最短路の親が入る
  dist[s] = 0;
  priority_queue<Edge<Weight>> q;
  q.emplace(-2, s, dist[s]);
  while (!q.empty()) {
    auto now = q.top();
    q.pop();
    int parent = now.from, u = now.to;
    if (prev[u] != -1) {
      continue;
    } else {
      prev[u] = parent;
    }
    for (auto e : g[u]) {
      int v = e.to;
      auto cost = get<0>(e.values);
      if (dist[v] > dist[u] + cost) {
        dist[v] = dist[u] + cost;
        q.emplace(u, v, dist[v]);
      }
    }
  }
  return make_pair(dist, prev);
}

/*
int main() {
  cin.sync_with_stdio(false);
  int n, m, root;
  cin >> n >> m >> root;
  Graph<Weight> g(n);
  for (int i = 0; i < m; ++i) {
    int s, t;
    Weight d;
    cin >> s >> t >> d;
    g.AddEdge(s, t, d);
  }
  auto dist = Dijkstra(g, root).first;
  for (int i = 0; i < n; ++i) {
    if (dist[i] == INF64)
      cout << "INF" << endl;
    else
      cout << dist[i] << endl;
  }
}
*/
// be checked by AOJ(GRL-1-A).