#pragma once

#include <bits/stdc++.h>

// 1-indexed
template <typename T> class BinaryIndexedTree {
  int N;
  std::vector<T> bit;

public:
  BinaryIndexedTree(int n) : N(n), bit(n + 1, 0) {}

  void add(int index, T num) {
    for (int x = index; x <= N; x += x & -x)
      bit[x] += num;
  }

  T sum(int index) {
    T ret = 0;
    for (int x = index; x > 0; x -= x & -x)
      ret += bit[x];
    return ret;
  }

  // sum of [left, right)
  T sum(int left, int right) { return sum(right - 1) - sum(left - 1); }
};
