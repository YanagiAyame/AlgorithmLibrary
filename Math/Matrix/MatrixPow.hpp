#pragma once

#include "typedef.hpp"

template <typename Type>
Matrix<Type> matrix_pow(Matrix<Type> a, long long int k) {
  Matrix<Type> ret(a.get_row(), a.get_col(), true);
  for (; k > 0; k >>= 1) {
    if (k & 1)
      ret = ret * a;
    a = a * a;
  }
  return ret;
}
