#pragma once

// verified
// https://beta.atcoder.jp/contests/atc001/submissions/3497697
// 整数値が欲しいときで誤差をなくしたいときは NTT を使う

#include <cmath>
#include <complex>
#include <vector>

const double pi = acos(-1.0);

using data_type = std::complex<double>;

// inv==trueで逆変換
std::vector<data_type> fft(std::vector<data_type> v, bool inv = false) {
  const int n = v.size();
  double theta = 2 * pi / n * (inv ? -1 : 1);
  for (int m = n; m >= 2; m >>= 1) {
    int mh = m >> 1;
    std::complex<double> theta_i(0, theta);
    for (int i = 0; i < mh; ++i) {
      auto w = exp((data_type)i * theta_i);
      for (int j = i; j < n; j += m) {
        auto x = v[j] - v[j + mh];
        v[j] = v[j] + v[j + mh];
        v[j + mh] = w * x;
      }
    }
    theta *= 2;
  }
  int i = 0;
  for (int j = 1; j < n - 1; ++j) {
    for (int k = n >> 1; k > (i ^= k); k >>= 1)
      ;
    if (j < i) {
      swap(v[i], v[j]);
    }
  }
  if (inv) {
    for (auto &x : v) {
      x /= n;
    }
  }
  return v;
}

std::vector<data_type> convolution(std::vector<data_type> x,
                                   std::vector<data_type> y) {
  int n = 1;
  int t = x.size() + y.size();
  while (n < t) {
    n <<= 1;
  }
  x.resize(n);
  y.resize(n);
  x = fft(move(x));
  y = fft(move(y));
  for (int i = 0; i < n; ++i) {
    x[i] *= y[i];
  }
  x = fft(move(x), true);
  return x;
}
