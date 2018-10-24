#pragma once

#include <algorithm>
#include <cassert>
#include <queue>
#include <vector>

constexpr long long INF64 = 1e18;

class Graph {

  struct Edge {
    int src, dst;
    long long weight;
    Edge(int src, int dst, long long weight)
        : src(src), dst(dst), weight(weight) {}
  };

  std::vector<std::vector<Edge>> g;
  std::vector<long long> dist, prev;

  bool negative_cycle = false;

public:
  Graph(int n) : g(n), dist(n, INF64), prev(n, -1) {}

  void addEdge(int s, int t, int cost) { g[s].emplace_back(s, t, cost); }

  std::vector<long long> BellmanFord(int s) {
    const int n = g.size();
    dist[s] = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        for (auto e : g[j]) {
          if (dist[e.src] != INF64 && dist[e.dst] > dist[e.src] + e.weight) {
            dist[e.dst] = dist[e.src] + e.weight;
            prev[e.dst] = e.src;
            if (i == n - 1) {
              dist[e.dst] = -INF64;
              negative_cycle = true;
            }
          }
        }
      }
    }
    return dist;
  }

  std::vector<int> getPath(int t) {
    assert(t != -INF64);
    std::vector<int> path;
    for (; t != -2; t = prev[t]) {
      path.push_back(t);
    }
    std::reverse(path.begin(), path.end());
    return path;
  }

  bool NegativeCycle = negative_cycle;
}
