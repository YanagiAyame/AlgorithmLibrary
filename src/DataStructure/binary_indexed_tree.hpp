#pragma once

#include <vector>

// Runs add queries and range sum queries.
// Add : O(log n)
// Sum : O(log n)
template <class Abel>
class BinaryIndexedTree
{
  const int size_;
  std::vector<Abel> data_;

public:
  BinaryIndexedTree(int size) : size_(size), data_(size + 1, 0) {}

  // data[target] += num
  void Add(int target, Abel num)
  {
    for (int index = target + 1; index <= size_; index += index & -index)
      data_[index] += num;
  }

  // sum of [0, right)
  Abel Sum(int right)
  {
    Abel sum = 0;
    for (int index = right; index > 0; index -= index & -index)
      sum += data_[index];
    return sum;
  }

  // sum of [left, right)
  Abel Sum(int left, int right) { return Sum(right) - Sum(left); }
};