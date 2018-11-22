#pragma once

#include <vector>

template <typename Type> class Matrix {
private:
  std::vector<std::vector<Type>> mat;

public:
  Matrix() = default;
  Matrix(Matrix &&) = default;
  Matrix &operator=(Matrix &&) = default;
  Matrix(const Matrix &) = default;
  Matrix &operator=(const Matrix &) = default;
  ~Matrix() = default;

  Matrix(std::initializer_list<std::vector<Type>> init) : mat(init) {}
  Matrix(int R, int C, bool is_identity = false) {
    mat = std::vector<std::vector<Type>>(R, std::vector<Type>(C));
    if (is_identity) {
      assert(R == C);
      for (int i = 0; i < R; i++) {
        mat[i][i] = Type(1);
      }
    }
  }

  int row() const { return mat.size(); }
  int col() const { return mat.front().size(); }

  std::vector<Type> &operator[](unsigned int x) { return mat[x]; }
  const std::vector<Type> &operator[](unsigned int x) const { return mat[x]; }

  bool operator==(const Matrix &m) { return mat == m.mat; }

  template <typename F> Matrix &apply(F f) {
    for (auto &x : elems)
      f(x);
    return *this;
  }

  template <typename M, typename F>
  Enable_if<Matrix_type<M>(), Matrix &> apply(const M &m, F f) {
    assert(row() == m.row() && col() == m.col());
    for (auto i = begin(), j = m.begin(); i != end(); ++i, ++j)
      f(*i, *j);
    return *this;
  }

  template <typename M>
  Enable_if<Matrix_type<M>(), Matrix &> operator+=(const M &x) {
    return apply(m, [](T &a, const Value_type<M> &b) { a += b; });
  }
};

template <typename T>
Matrix<T> operator+(const Matrix<T> &a, const Matrix<T> &b) {
  Matrix<T, N> res = a;
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
        ret[i][j] += (a[i][k] * b[k][j]);
      }
    }
  }
  return res;
}
