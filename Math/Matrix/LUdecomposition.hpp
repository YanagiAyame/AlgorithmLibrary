#pragma once

#include "typedef.hpp"
#include <cassert>
#include <cmath>

template <typename Type> struct LU_type {
  Matrix<Type> mat;
  std::vector<int> pivots;
};

// A => LU
// verified
template <typename Type> LU_type<Type> LUdecomposer(Matrix<Type> A) {

  assert(A.get_col() == A.get_row());

  const int n = A.get_col();
  std::vector<int> pivots(n);

  for (int j = 0; j < n; ++j) {
    //上三角行列を生成
    for (int i = 0; i <= j; ++i) {
      for (int k = 0; k < i; ++k) {
        A[i][j] -= A[i][k] * A[k][j];
      }
    }
    // pivot選択をしつつ下三角行列を計算
    int pivot = j;
    int ma = 1; // L[j][j] == 1 としているため
    for (int i = j + 1; i < n; ++i) {
      for (int k = 0; k < j; ++k) {
        A[i][j] -= A[i][k] * A[k][j];
      }
      if (ma < A[i][j]) {
        pivot = i;
        ma = A[i][j];
      }
    }
    pivots[j] = pivot;

    // pivot選択に従って入れ替え
    std::swap(A[pivot], A[j]);
    for (int i = j + 1; i < n; ++i) {
      A[i][j] /= A[j][j];
    }
  }
  return {A, pivots};
}

// find x : Ax = (LU)x = L(Ux) = Ly = b
// verified
template <typename Type>
std::vector<Type> LUsolver(const LU_type<Type> &LU, std::vector<Type> b) {

  const auto &A = LU.mat;
  const auto &pivots = LU.pivots;

  const int n = pivots.size();

  for (int i = 0; i < n; ++i) {
    std::swap(b[i], b[pivots[i]]);
  }

  // Ly = b を解く
  //前進代入
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
      b[i] -= A[i][j] * b[j];
    }
  }

  // Ux = y を解く
  //後退代入
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i + 1; j < n; ++j) {
      b[i] -= A[i][j] * b[j];
    }
    b[i] /= A[i][i];
  }

  return b;
}

// to do verify
template <typename Type> Matrix<Type> Inv(Matrix<Type> A) {
  const int n = A.get_col();
  auto lu = LUdecomposer(A);
  vector<Type> b(n);
  for (int i = 0; i < n; ++i) {
    if (i) {
      b[i - 1] = (Type)(0);
    }
    b[i] = (Type)(1);
    auto x = LUsolver(lu, b);
    for (int j = 0; j < n; ++j) {
      A[j][i] = 0;
    }
  }
  return A;
}
