#pragma once

#include <map>
#include <string>
#include <vector>

class RollingHash {
  using ull = unsigned long long;

private:
  int n_;
  std::vector<ull> hash1_, hash2_, pow1_, pow2_;
  static const ull kBase1 = 1009;
  static const ull kBase2 = 10007;
  static const ull kMod1 = 999999937;
  static const ull kMod2 = 1000000007;

public:
  RollingHash(const std::string &s)
      : n_(s.size()), hash1_(n_ + 1), hash2_(n_ + 1), pow1_(n_ + 1, 1),
        pow2_(n_ + 1, 1) {
    for (int i = 1; i <= n_; ++i) {
      pow1_[i] = pow1_[i - 1] * kBase1 % kMod1;
      pow2_[i] = pow2_[i - 1] * kBase2 % kMod2;
      hash1_[i] = (hash1_[i - 1] * kBase1 + s[i - 1]) % kMod1;
      hash2_[i] = (hash2_[i - 1] * kBase2 + s[i - 1]) % kMod2;
    }
  }
  // 0indexedで半開区間[l,r)
  std::pair<ull, ull> get(int l, int r) {
    return {(hash1_[r] - hash1_[l] * pow1_[r - l] % kMod1 + kMod1) % kMod1,
            (hash2_[r] - hash2_[l] * pow2_[r - l] % kMod2 + kMod2) % kMod2};
  }
};
