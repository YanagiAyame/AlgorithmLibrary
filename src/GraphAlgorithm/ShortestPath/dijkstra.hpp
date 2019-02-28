#pragma once

#include <vector>
#include <queue>
#include <tuple>
#include <utility>

#include "../graph_type.hpp"

using Weight = long long;
constexpr long long kWEIGHT_INF = 1e18;

template <class... Args>
auto Dijkstra(const auto &g, int s)
{
  const int n = g.size();
  std::vector<Weight> dist(n, kWEIGHT_INF); //各点における始点sからの距離が入る
  std::vector<int> prev(n, -1);             //各点における最短路の親が入る
  dist[s] = 0;
  std::priority_queue<Edge<Weight>> q;
  q.emplace(-2, s, dist[s]);
  while (!q.empty())
  {
    auto now = q.top();
    q.pop();
    int parent = now.from, u = now.to;
    if (prev[u] != -1)
    {
      continue;
    }
    else
    {
      prev[u] = parent;
    }
    for (const auto &e : g[u])
    {
      int v = e.to;
      auto cost = std::get<0>(e.values);
      if (dist[v] > dist[u] + cost)
      {
        dist[v] = dist[u] + cost;
        q.emplace(u, v, dist[v]);
      }
    }
  }
  return std::make_pair(dist, prev);
}