#include <vector>

class CompactDataStructure {
  std::vector<bool> data_;
  std::vector<int> rank_, select0_, select1_;

public:
  template <typename T = std::vector<bool>>
  CompactDataStructure(T &&data) : data_(data), rank_(data_.size() + 1) {
    const int kSize = data_.size();
    for (int i = 0; i < kSize; ++i) {
      rank_[i + 1] = rank_[i] + data_[i];
      (data[i] ? select1_ : select0_).push_back(i);
    }
  }
  int rank(int i, bool f) const { return f ? rank_[i] : i - rank_[i]; }
  int rank(int l, int r, bool f) const { return rank(r, f) - rank(l, f); }
  int select(int x, bool f) const { return (f ? select1_ : select0_)[x]; }
  int select(int l, int x, bool f) const { return select(x + rank(l, f), f); }
};

template <typename Z> class WaveletMatrix {
  Z max_bit_;
  vector<CompactDataStructure> data_;
  vector<int> mid_;

  Z FindMaxBit(Z val) {
    int res = 1;
    for (long long i = 1; (i <<= 1) <= val; ++res)
      ;
    return res;
  }

public:
  WaveletMatrix(const vector<T> &data)
      : max_bit_(FindMaxBit(*std::max_element(data.begin(), data.end()))),
        mid_(max_bit_) {
    const int kSize = data.size();
    data_.assign(max_bit_, kSize);
  }
}