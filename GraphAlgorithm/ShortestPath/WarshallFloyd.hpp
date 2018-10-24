#pragma once

#include <algorithm>
#include <vector>

constexpr long long INF64 = 1e18;

class Graph {
  std::vector<std::vector<long long>> g, dist;

  bool flag = false;

  void WarshallFloyd() {
    const int n = g.size();
    for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
          if (dist[i][j] < dist[i][k] + dist[k][j]) {
            dist[i][j] = dist[i][k] + dist[k][j];
          }
        }
      }
    }
    flag = true;
  }

public:
  Graph(int n)
      : g(n, std::vector<long long>(n)), dist(n, std::vector<long long>(n)) {}

  void addEdge(int s, int t, long long cost) {
    g[s][t] = std::min(g[s][t], cost);
    flag = false;
  }

  long long getCost(int s, int t) {
    if (!flag) {
      WarshallFloyd();
    }
    return dist[s][t];
  }
}