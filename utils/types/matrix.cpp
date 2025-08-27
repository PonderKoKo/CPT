#include "../macros.h"

template<typename T, auto f = multiplies{}, auto g = plus{}, auto fn = 1, auto gn = 0>
struct Matrix {
    Table<T> a;
    Matrix(const Table<T>& t) : a{t} {}
    Matrix(int r, int c, T x = gn) : a(r, vector(c, x)) {}
    Matrix(int rc = 0) : Matrix(rc, rc) { rep(i, rc) a[i][i] = fn; }
    Matrix operator* (const Matrix& o) const {
        Matrix m(size(a), size(o.a[0]));
        rep(i, size(a)) rep(k, size(a[0])) rep(j, size(o.a[0]))
            m.a[i][j] = g(m.a[i][j], f(a[i][k], o.a[k][j]));
        return m;
    }
    Matrix& em(Matrix m, num p) {
        for (; p; p /= 2, m *= m)
            if (p & 1)
                *this *= m;
        return *this;
    }
    Matrix operator^ (num p) const { return Matrix(size(a)).em(*this, p); }
    Matrix& operator*= (const Matrix& other) { return *this = *this * other; }
};
template<typename T> using MinPlusMatrix = Matrix<T,plus{},ranges::min,0,numeric_limits<T>::max() / 2>;
template<typename T> using MaxPlusMatrix = Matrix<T,plus{},ranges::max,0,numeric_limits<T>::min() / 2>;
