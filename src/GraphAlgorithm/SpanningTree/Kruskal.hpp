#pragma once

#include <queue>
#include <utility>

#include "../../DataStructure/union_find.hpp"
#include "../graph_type.hpp"

using Weight = long long;
// Kruskal's algorithm
// Finds a minimum-spanning-tree.
// Returns the sum of the tree's cost and the edges of the tree.
// Complexity : O(E log V)
template <class... Args>
auto Kruskal(const auto &g)
{
  const int n = g.size();
  UnionFind uf(n);
  std::priority_queue<Edge<Args...>> q;
  for (int i = 0; i < n; ++i)
  {
    for (const auto &e : g[i])
    {
      if (i < e.to)
      {
        q.push(e);
      }
    }
  }
  Weight total_cost = 0;
  Graph<Args...> forest(n);
  int forest_size = 0;
  while (forest_size < n - 1 && !q.empty())
  {
    auto e = q.top();
    q.pop();
    if (uf.unite(e.from, e.to))
    {
      forest.AddEdge(e);
      forest_size++;
      total_cost += std::get<0>(e.values);
    }
  }
  return std::make_pair(total_cost, forest);
}