#pragma once

#include "../../DataStructure/UnionFind.hpp"
#include "template.hpp"
#include <queue>
#include <utility>

std::pair<long long, Edges> kruskal(const Graph &g) {
  int n = g.size();
  UnionFind<int> uf(n);
  std::priority_queue<Edge> q;
  for (int i = 0; i < n; ++i) {
    for (auto e : g[i]) {
      if (i < e.dst)
        q.push(e);
    }
  }
  long long total = 0;
  Edges forest;
  while (forest.size() < n - 1 && !q.empty()) {
    Edge e = q.top();
    q.pop();
    if (uf.unite(e.src, e.dst)) {
      forest.push_back(e);
      total += e.weight;
    }
  }
  return {total, forest};
}
