#pragma once

#include <cassert>
#include <iostream>
#include <vector>

template <typename T> class Matrix {
private:
  std::vector<std::vector<T>> mat;

public:
  Matrix() = default;
  Matrix(Matrix &&) = default;
  Matrix &operator=(Matrix &&) = default;
  Matrix(const Matrix &) = default;
  Matrix &operator=(const Matrix &) = default;
  ~Matrix() = default;

  Matrix(std::initializer_list<std::vector<T>> init) : mat(init) {}
  Matrix(int R, int C, bool is_identity = false) {
    mat = std::vector<std::vector<T>>(R, std::vector<T>(C));
    if (is_identity) {
      assert(R == C);
      for (int i = 0; i < R; i++) {
        mat[i][i] = T(1);
      }
    }
  }

  int row() const { return mat.size(); }
  int col() const { return mat.front().size(); }

  std::vector<T> &operator[](unsigned int x) { return mat[x]; }
  const std::vector<T> &operator[](unsigned int x) const { return mat[x]; }

  template <typename F> Matrix<T> &apply(F f) {
    for (auto &elems : mat) {
      for (auto &x : elems) {
        f(x);
      }
    }
    return *this;
  }

  Matrix<T> &operator+=(const T &val) {
    return apply([&](T &a) { a += val; });
  }
  Matrix<T> &operator*=(const T &val) {
    return apply([&](T &a) { a += val; });
  }

  template <typename F> Matrix<T> &apply(const Matrix<T> &m, F f) {
    assert(row() == m.row() && col() == m.col());
    const int R = row(), C = col();
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        f(mat[i][j], m[i][j]);
      }
    }
    return *this;
  }

  Matrix<T> &operator+=(const Matrix<T> &m) {
    return apply(m, [](T &a, const T &b) { a += b; });
  }
};

template <typename T>
Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b) {
  Matrix<T> res = a;
  res += b;
  return res;
}

template <typename T>
Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &b) {
  assert(a.col() == b.row());
  const int R = a.row(), C = b.col(), X = a.col();
  Matrix<T> res(R, C);
  for (int i = 0; i < R; i++) {
    for (int k = 0; k < X; k++) {
      for (int j = 0; j < C; j++) {
        res[i][j] += (a[i][k] * b[k][j]);
      }
    }
  }
  return res;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &m) {
  const int R = m.row(), C = m.col();
  for (int i = 0; i < R; ++i) {
    for (int j = 0; j < C; ++j) {
      os << m[i][j] << ',';
    }
    os << std::endl;
  }
  return os;
}
