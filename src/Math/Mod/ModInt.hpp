#pragma once

#include <bits/stdc++.h>

using namespace std;

template <int MOD> class ModInt {
private:
  int x;

  ModInt inverse() const {
    int a = x, b = MOD, u = 1, v = 0;
    while (b) {
      auto t = a / b;
      a -= t * b;
      swap(a, b);
      u -= t * v;
      swap(u, v);
    }
    return ModInt(u);
  }

public:
  ModInt() = default;
  ModInt(ModInt &&) = default;
  ModInt &operator=(ModInt &&) = default;
  ModInt(const ModInt &) = default;
  ModInt &operator=(const ModInt &) = default;
  ~ModInt() = default;

  template <typename T> ModInt(T x) : x(((x % MOD) + MOD) % MOD) {}

  auto value() const { return x; }

  ModInt &operator+=(const ModInt &mx) {
    x = (x + mx.x) % MOD;
    return *this;
  }
  ModInt &operator-=(const ModInt &mx) {
    x = (x - mx.x + MOD) % MOD;
    return *this;
  }
  ModInt &operator*=(const ModInt &mx) {
    x = (int)((long long)x * mx.x % MOD);
    return *this;
  }
  ModInt &operator/=(const ModInt &mx) {
    x = (ModInt(x) * mx.inverse()).value();
    return *this;
  }
};
template <int MOD>
bool operator==(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
  return lhs.value() == rhs.value();
}
template <int MOD>
ModInt<MOD> operator+(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
  return ModInt<MOD>(lhs) += rhs;
}
template <int MOD>
ModInt<MOD> operator-(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
  return ModInt<MOD>(lhs) -= rhs;
}
template <int MOD>
ModInt<MOD> operator*(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
  return ModInt<MOD>(lhs) *= rhs;
}
template <int MOD>
ModInt<MOD> operator/(const ModInt<MOD> &lhs, const ModInt<MOD> &rhs) {
  return ModInt<MOD>(lhs) /= rhs;
}
template <int MOD> ostream &operator<<(ostream &os, const ModInt<MOD> &mx) {
  return os << mx.value();
}
template <int MOD> istream &operator>>(istream &is, ModInt<MOD> &mx) {
  long long x;
  is >> x;
  mx = ModInt<MOD>(x);
  return is;
}
