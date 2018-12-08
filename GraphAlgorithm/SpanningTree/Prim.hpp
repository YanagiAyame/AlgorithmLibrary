#pragma once

#include "template.hpp"
#include <queue>
#include <utility>

std::pair<long long, Edges> Prim(const Graph &g, int s) {
  int n = g.size();
  Edges tree;
  long long total = 0;
  std::vector<int> visited(n, 0);
  std::priority_queue<Edge> q;
  q.emplace(-1, s, 0);
  while (!q.empty()) {
    Edge e = q.top();
    q.pop();
    if (visited[e.dst])
      continue;
    if (e.src != -1)
      tree.push_back(e);
    total += e.weight;
    visited[e.dst] = true;
    for (auto f : g[e.dst]) {
      if (!visited[f.dst])
        q.push(f);
    }
  }
  return std::pair<long long, Edges>(total, tree);
}
