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
    // pivot選択
    int pivot = j;
    auto ma = std::fabs(A[pivot][j]);
    for (int i = 0; i < n; ++i) {
      auto abs_now = std::fabs(A[i][j]);
      if (ma < abs_now) {
        pivot = i;
        ma = abs_now;
      }
    }
    pivots[j] = pivot;

    // pivot選択に従って入れ替え
    std::swap(A[pivot], A[j]);

    //三角行列を生成
    for (int i = 0; i <= j; ++i) {
      for (int k = 0; k < i; ++k) {
        A[i][j] -= A[i][k] * A[k][j];
      }
    }
    for (int i = j + 1; i < n; ++i) {
      for (int k = 0; k < j; ++k) {
        A[i][j] -= A[i][k] * A[k][j];
      }
      A[i][j] /= A[j][j];
    }
  }
  return {A, pivots};
}

// find x : Ax = (LU)x = L(Ux) = Ly = b
// to do verify
template <typename Type>
std::vector<Type> LUsolver(const lu_data &LU, std::vector<Type> b) {

  const auto &A = LU.A;
  const auto &pivots = LU.pivots;

  const int n = pivots.size();

  for (int i = 0; i < n; ++i) {
    std::swap(b[i], b[pivots[n - i - 1]]);
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
