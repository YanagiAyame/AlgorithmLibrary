#pragma once

#include <vector>

// Runs range sum queries only.
// Sum : O(1)
template <class Abel>
class CumulativeSum
{
  std::vector<T> _sums;

public:
  CumulativeSum(const vector<T> &v) : _sums(v)
  {
    _sums.insert(_sums.begin(), 0);
    for (int i = 1; i < (int)_sums.size(); ++i)
    {
      _sums[i] += _sums[i - 1];
    }
  }

  // sum of [1, index]
  T sum(int index) { return _sums[index]; }

  // sum of [left, right)
  T sum(int left, int right) { return sum(right - 1) - sum(left - 1); }
};
