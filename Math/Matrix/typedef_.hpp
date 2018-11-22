#pragma once

#include <vector>

template <typename T, size_t N> class Matrix {
private:
  Matrix_slice<N> desc;
  std::vector<T> elems;

public:
  static constexpr size_t order = N; //次元数

  Matrix() = default;
  Matrix(Matrix &&) = default;
  Matrix &operator=(Matrix &&) = default;
  Matrix(const Matrix &) = default;
  Matrix &operator=(const Matrix &) = default;
  ~Matrix() = default;

  template <typename U> Matrix(const Matrix_ref<U, N> &);
  template <typename U> Matrix &operator=(const Matrix_ref<U, N> &);

  template <typename... Exts> explicit Matrix(Exts... exts);

  Matrix(Matrix_initializer<T, N>);
  Matrix &operator=(Matrix_initializer<T, N>);

  template <typename U> Matrix(initializer_list<U>) = delete;
  template <typename U> Matrix &operator=(initializer_list<U>) = delete;

  size_t extent(size_t n) const { return desc.extents[n]; }

  size_t size() const { return elems.size(); }

  const Matrix_slice<N> &descriptor() const { return desc; }

  T *data() { return elems.data(); }
  const T *data() const { return elems.data(); }

  template <typename... Args>
  Enable_if<Matrix_impl::Requesting_element<Args...>(), T &>
  operator()(Args... args);

  template <typename... Args>
  Enable_if<Matrix_impl::Requesting_element<Args...>(), T &>
  operator()(Args... args) const;

  template <typename... Args>
  Enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<T, N>>
  operator()(const Args &... args);

  template <typename... Args>
  Enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<const T, N>>
  operator()(const Args &... args) const;

  Matrix_ref<T, N - 1> operator[](size_t i) { return row(i); }
  Matrix_ref<const T, N - 1> operator[](size_t i) const { return row(i); }

  Matrix_ref<T, N - 1> row(size_t n);
  Matrix_ref<const T, N - 1> row(size_t n) const;

  Matrix_ref<T, N - 1> col(size_t n);
  Matrix_ref<const T, N - 1> col(size_t n) const;

  template <typename F> Matrix &apply(F f);

  template <typename M, typename F>
  Enable_if<Matrix_type<M>(), Matrix &> apply(const M &m, F f);

  Matrix &operator=(const T &value);
  Matrix &operator+=(const T &value);
  Matrix &operator-=(const T &value);
  Matrix &operator*=(const T &value);
  Matrix &operator/=(const T &value);
  Matrix &operator%=(const T &value);

  template <typename M>
  Enable_if<Matrix_type<M>(), Matrix &> operator+=(const M &x);

  template <typename M>
  Enable_if<Matrix_type<M>(), Matrix &> operator-=(const M &x);

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

template <typename T, size_t N>
template <typename... Exts>
Matrix<T, N>::Matrix(Exts... exts) : desc{exts...}, elems(desc.size) {}

template <typename T, size_t N>
Matrix<T, N>::Matrix(Matrix_initializer<T, N> init) {
  desc.extents = Matrix_impl::derive_extents(init);
  Matrix_impl::compute_stride(desc);
  elems.reserve(desc.size);
  Matrix_impl::insert_flat(init, elems);
  assert(elems.size() == desc.size);
}

template <typename T, size_t N>
template <typename U>
Matrix<T, N>::Matrix(const Matrix_ref<U, N> &x)
    : desc{x.desc}, elems{x.begin(), x.end} {
  static_assert(Convertible<U, T>(),
                "Matrix constructor; incompatible element types");
}

template <typename T, size_t N>
template <typename U>
Matrix<T, N> &Matrix<T, N>::operator=(const Matrix_ref<U, N> &x) {
  static_assert(Convertible<U, T>(),
                "Matrix constructor; incompatible element types");
  desc = x.desc;
  elems.assign(x.begin(), x.end());
  return *this;
}

template <typename T, size_t N>
Matrix_ref<T, N - 1> Matrix<T, N>::operator[](size_t n) {
  return row(n);
}

template <typename T, size_t N>
Matrix<T, N> &Matrix<T, N>::operator+=(const T &val) {
  return apply([&](T &a) { a += val; });
}

template <typename T, size_t N>
template <typename F>
Matrix<T, N> &Matrix<T, N>::apply(F f) {
  for (auto &x : elems)
    f(x);
  return *this;
}

template <typename T, , size_t N>
Matrix<T, N> operator+(const Matrix<T, N> &m, const T &val) {
  Matrix<T, N> res = m;
  res += val;
  return res;
}

template <typename T, , size_t N>
Matrix<T, N> operator-(const Matrix<T, N> &m, const T &val) {
  Matrix<T, N> res = m;
  res -= val;
  return res;
}

template <typename T, , size_t N>
Matrix<T, N> operator*(const Matrix<T, N> &m, const T &val) {
  Matrix<T, N> res = m;
  res *= val;
  return res;
}

template <typename T, , size_t N>
Matrix<T, N> operator/(const Matrix<T, N> &m, const T &val) {
  Matrix<T, N> res = m;
  res /= val;
  return res;
}

template <typename T, , size_t N>
Matrix<T, N> operator%(const Matrix<T, N> &m, const T &val) {
  Matrix<T, N> res = m;
  res %= val;
  return res;
}

template <typename T, size_t N>
template <typename M>
Enable_if<Matrix_type<M>(), Matrix<T, N> &> Matrix<T, N>::
operator+=(const M &m) {
  static_assert(m.order == N, "+=: mismatched Matrix dimensions");
  assert(same_extents(desc, m.descriptor()));

  return apply(m, [](T &a, const Value_type<M> &b) { a += b; });
}

template <typename T, size_ t N>
template <typename M, typename F>
Enable_ if<Matrix_ type<M>(), Matrix<T, N> &> Matrix<T, N>::apply(M &m, F f) {
  assert(same_extents(desc, m.descriptor()));

  for (auto i = begin(), j = m.begin(); i != end(); ++i, ++j)
    f(*i, *j);
  return *this;
}

template <typename T, size_t N>
Matrix<T, N> operator+(const Matrix<T, N> &a, const Matrix<T, N> &b) {
  Matrix<T, N> res = a;
  res += b;
  return res;
}

template <size_t N> struct Matrix_slice {
  Matrix_slice() = default;
  Matrix_slice(size_t offset, initializer_list<size_t> exts);
  Matrix_slice(size_t offset, initializer_list<size_t> exts,
               initializer_list<size_t> strs);

  template <typename... Dims> Matrix_slice(Dims... dims);

  template <typename... Dims,
            typename = Enable_if<All(Convertible<Dims, size_t>()...)>>
  size_t operator()(Dims... dims) const;

  size_t size;
  size_t start;
  array<size_t, N> extents;
  array<syze_t, N> strides;
};

template <size_t N>
template <typename... Dims>
size_t Matrix_slice<N>::operator()(Dims... dims) const {
  static_assert(sizeof...(Dims) == N,
                "Matrix_slice<N>::operator(): dimension mismatch");
  size_t args[N]{size_t(dims)...};

  return start + inner_product(args, args + N, strides, begin(), size_t{0});
}

// to do
Matrix_ref