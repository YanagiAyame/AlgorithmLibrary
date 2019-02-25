#pragma once

#include <bits/stdc++.h>

using namespace std;

template <unsigned kMod> class RollingHash {
  using ull = unsigned long long;

private:
  const int _kN;
  std::vector<unsigned> _hash, _pow;
  unsigned _kBase;

public:
  RollingHash(const std::string &s)
      : _kN(s.size()), _hash(_kN + 1), _pow(_kN + 1, 1) {
    std::random_device seed_gen;
    std::mt19937_64 engine(seed_gen());
    _kBase = engine() % (kMod - 2) + 2;
    for (int i = 1; i <= _kN; ++i) {
      _pow[i] = (unsigned)((ull)_pow[i - 1] * _kBase % kMod);
      _hash[i] = (unsigned)(((ull)_hash[i - 1] * _kBase + s[i - 1]) % kMod);
    }
  }

  // 0-indexedで半開区間[l,r)
  ull get(int l, int r) {
    return (_hash[r] - (ull)_hash[l] * _pow[r - l] % kMod + kMod) % kMod;
  }
};

/*
int main() {
  int n, m;
  cin >> n >> m;
  string s;
  cin >> s;
  RollingHash<1000000009> hashed_str1(s);
  RollingHash<1000000007> hashed_str2(s);
  int r = 1, l = 1;
  set<pair<unsigned, unsigned>> sub;
  for (int i = 0; i < m; ++i) {
    string q;
    cin >> q;
    if (q == "L++") {
      l++;
    }
    if (q == "L--") {
      l--;
    }
    if (q == "R++") {
      r++;
    }
    if (q == "R--") {
      r--;
    }
    sub.insert({hashed_str1.get(l - 1, r), hashed_str2.get(l - 1, r)});
  }
  cout << sub.size() << endl;
}
*/
// be checked by AOJ-2444.