#pragma once

#include <vector>

template <typename T> class BinaryIndexedTree { // 1-indexed
  int N;
  std::vector<T> bit;

public:
  BinaryIndexedTree(int n) : N(n), bit(n + 1, 0) {}

  void add(int index, T num) {
    for (int x = index; x <= N; x += x & -x)
      bit[x] += num;
  }

  T sum(int index) {
    int ret = 0;
    for (int x = index; x > 0; x -= x & -x)
      ret += bit[x];
    return ret;
  }
};
