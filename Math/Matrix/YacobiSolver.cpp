#pragma once

#include <bits/stdc++.h>

constexpr long double eps = 1e-15;

template <typename Type = long double> class Matrix {
private:
  std::vector<std::vector<Type>> mat;

public:
  Matrix(std::initializer_list<std::vector<Type>> l) : mat(l) {}
  Matrix(int R, int C, bool is_identity = false) {
    mat = std::vector<std::vector<Type>>(R, std::vector<Type>(C));
    if (is_identity) {
      assert(R == C);
      for (int i = 0; i < R; i++) {
        mat[i][i] = Type(1);
      }
    }
  }
  int get_row() const { return mat.size(); }
  int get_col() const { return mat.front().size(); }
  std::vector<Type> &operator[](unsigned int x) { return mat[x]; }
  const std::vector<Type> &operator[](unsigned int x) const { return mat[x]; }
  Matrix &operator=(const Matrix &a) {
    assert(this->get_row() == a.get_row());
    assert(this->get_col() == a.get_col());
    mat = a.mat;
    return *this;
  }
  bool operator==(const Matrix &a) { return mat == a.mat; }
  Matrix &operator+=(Matrix &a) {
    int R = this->get_row, C = this->get_col;
    assert(R == a.get_row());
    assert(C == a.get_col());
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        // caution (operation)
        (*this)[i][j] += a[i][j];
      }
    }
    return *this;
  }
  Matrix operator+(Matrix a) { return (*this) += a; }
  Matrix operator*(Matrix a) {
    assert(this->get_col() == a.get_row());
    int R_ret = this->get_row(), C_ret = a.get_col(), X = this->get_col();
    Matrix<Type> ret(R_ret, C_ret);

    for (int i = 0; i < R_ret; i++) {
      for (int k = 0; k < X; k++) {
        for (int j = 0; j < C_ret; j++) {
          // caution (operation)
          ret[i][j] += ((*this)[i][k] * a[k][j]);
        }
      }
    }
    return ret;
  }
  Matrix &operator*=(Matrix a) {
    *this = (*this) * a;
    return *this;
  }
};

// find x (Ax=b)
// verified
template <typename Type>
std::vector<Type> YacobiSolver(const Matrix<Type> &A,
                               const std::vector<Type> &b) {
  const int n = A.get_col();
  assert(n == A.get_row());

  std::vector<Type> X(n);
  std::vector<Type> newX(n);

  bool flag = true;

  while (flag) {
    flag = false;
    for (int i = 0; i < n; ++i) {
      Type C(0);
      for (int j = 0; j < n; ++j) {
        if (i == j) {
          continue;
        }
        C += A[i][j] * X[j];
      }
      newX[i] = (b[i] - C) / A[i][i];
      if (fabs(newX[i] - X[i]) > (Type)eps) {
        flag = true;
      }
    }
    X = newX;
  }
  return X;
}

using namespace std;

int main() {
  int n;
  cin >> n;
  // n次正方行列
  Matrix<double> A(n, n, true);
  double a;
  //行列要素の一部を入力
  cin >> a;
  A[0][n - 1] = a;
  A[n - 1][0] = a;
  for (int i = 0; i < n; ++i) {
    if (i == 0) {
      A[i][i + 1] = a;
    } else if (i == n - 1) {
      A[i][i - 1] = a;
    } else {
      A[i][i - 1] = A[i][i + 1] = a;
    }
  }
  vector<double> b(n, 0);
  b[0] = 1;
  b[n - 1] = -1;

  auto ans = YacobiSolver(A, b);

  for (const auto &x : ans) {
    cout << x << endl;
  }
}
