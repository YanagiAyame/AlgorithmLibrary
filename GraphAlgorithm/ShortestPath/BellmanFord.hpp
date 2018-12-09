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

template <class G> auto BellmanFord(const G &g, int s) {
  const int n = (int)g.size();
  vector<Weight> dist(n, INF64); //各点における始点sからの距離が入る
  vector<int> prev(n, -1);       //各点における最短路の親が入る
  dist[s] = 0;
  bool negative_cycle = false; // 負閉路検出
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (const auto &e : g[j]) {
        int u = e.from, v = e.to;
        Weight cost = get<0>(e.values);
        if (dist[u] != INF64 && dist[v] > dist[u] + cost) {
          dist[v] = dist[u] + cost;
          prev[v] = u;
          if (i == n - 1) {
            dist[v] = -INF64;
            negative_cycle = true;
          }
        }
      }
    }
  }
  return make_tuple(negative_cycle, dist, prev);
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
    g[s].emplace_back(s, t, d);
  }
  auto ans = BellmanFord(g, root);
  if (get<0>(ans)) {
    cout << "NEGATIVE CYCLE" << endl;
  } else {
    auto dist = move(get<1>(ans));
    for (int i = 0; i < n; ++i) {
      if (dist[i] == INF64)
        cout << "INF" << endl;
      else
        cout << dist[i] << endl;
    }
  }
}*/
// be checked by AOJ(GRL-1-B).