#include "typedef.hpp"
#include <cmath>

constexpr long double eps = 1e-15;

// find x (Ax=b)
// verified
template <typename Type>
std::vector<Type> JacobiSolver(const Matrix<Type> &A,
                               const std::vector<Type> &b) {
  const int n = A.col();
  assert(n == A.row());

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
  Matrix<long double> A(n, n, true);
  long double a;
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
  vector<long double> b(n, 0);
  b[0] = 1;
  b[n - 1] = -1;

  auto ans = JacobiSolver(A, b);

  for (const auto &x : ans) {
    cout << x << endl;
  }
}
