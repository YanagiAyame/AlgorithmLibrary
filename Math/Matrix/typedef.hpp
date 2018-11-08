#pragma once

#include <vector>

template <typename Type> class Matrix {
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
    mat = a.mat;
    return *this;
  }
  Matrix(const Matrix &a) { (*this) = a; }
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
