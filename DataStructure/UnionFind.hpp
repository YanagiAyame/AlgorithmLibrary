#pragma once

#include <bits/stdc++.h>

template <typename T = int> struct UnionFind {
  std::vector<T> data;
  UnionFind(int n) : data(n, -1) {}
  bool unite(T x, T y) {
    x = root(x);
    y = root(y);
    if (x != y) {
      if (data[y] < data[x])
        swap(x, y);
      data[x] += data[y];
      data[y] = x;
    }
    return x != y;
  }
  T root(T x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
  bool same(T x, T y) { return root(x) == root(y); }
  T size(T x) { return -data[root(x)]; }
};
