#pragma once

#include <vector>

// Runs range sum queries only.
// Sum : O(1)
template <class Abel>
class CumulativeSum
{
  std::vector<Abel> sums_;

public:
  CumulativeSum(const std::vector<Abel> &data) : sums_(data)
  {
    sums_.insert(sums_.begin(), Abel(0));
    for (int i = 1; i < (int)sums_.size(); ++i)
    {
      sums_[i] += sums_[i - 1];
    }
  }

  // Gets the sum of data[0, right)
  Abel Sum(int right) { return sums_[right]; }

  // Gets the sum of data[left, right)
  Abel Sum(int left, int right) { return Sum(right) - Sum(left); }
};