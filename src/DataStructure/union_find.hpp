#pragma once

#include <vector>

// Connects a set of subsets and checks the belonging of the data.
// unite : near O(1)
// root : near O(1)
// same : near O(1)
// size : near O(1)
class UnionFind
{
  using Abel = int;
  std::vector<Abel> data;

public:
  UnionFind(int n) : data(n, -1) {}

  // Connects between x and y.
  bool unite(Abel x, Abel y)
  {
    x = root(x);
    y = root(y);
    if (x != y)
    {
      if (data[y] < data[x])
      {
        std::swap(x, y);
      }
      data[x] += data[y];
      data[y] = x;
    }
    return x != y;
  }

  // Finds the belonging of x.
  Abel root(Abel x) { return data[x] < 0 ? x : data[x] = root(data[x]); }

  // Checks where x and y belong to the same subset.
  bool same(Abel x, Abel y) { return root(x) == root(y); }

  // Look up the size of the subset belonged to x.
  Abel size(Abel x) { return -data[root(x)]; }
};