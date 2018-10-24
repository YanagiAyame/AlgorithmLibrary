#pragma once

#include <algorithm>
#include <queue>
#include <vector>

constexpr long long INF64 = 1e18;

class Graph {

  struct Edge {
    int src, dst;
    long long weight;
    Edge(int src, int dst, long long weight)
        : src(src), dst(dst), weight(weight) {}

    bool operator<(const Edge &e) const {
      if (weight != e.weight)
        return weight > e.weight;
    }
  };

  std::vector<std::vector<Edge>> g;
  std::vector<long long> dist, prev;

  int flag = -1;

  void Dijkstra(int s) {
    std::priority_queue<Edge> q;
    dist[s] = 0;
    for (q.emplace(-2, s, 0); !q.empty();) {
      Edge e = q.top();
      q.pop();
      if (prev[e.dst] != -1) {
        continue;
      }
      prev[e.dst] = e.src;
      for (auto next_e : g[e.dst]) {
        if (dist[next_e.dst] > next_e.weight + e.weight) {
          dist[next_e.dst] = next_e.weight + e.weight;
          q.emplace(next_e.src, next_e.dst, dist[next_e.dst]);
        }
      }
    }
    flag = s;
  }

public:
  Graph(int n) : g(n), dist(n, INF64), prev(n, -1) {}

  void addEdge(int s, int t, long long cost) { g[s].emplace_back(s, t, cost); }

  long long getCost(int s, int t) {
    if (flag != s) {
      Dijkstra(s);
    }
    return dist[t];
  }

  std::vector<int> getPath(int t) {
    std::vector<int> path;
    for (; t != -2; t = prev[t]) {
      path.push_back(t);
    }
    std::reverse(path.begin(), path.end());
    return path;
  }
}
