#include "../macros.h"

template<typename T>
struct Matrix {
    Table<T> a;

    explicit Matrix(const Table<T>& t) : a{t} {}
    explicit Matrix(const vector<T>& v) : a{v} {}
    Matrix(int r, int c) : a(r, vector<T>(c)) {}
    explicit Matrix(int rc, bool id = false) : Matrix(rc, rc) {
        if (id) rep(i, rc) a[i][i] = 1;
    }

    int rows() const { return size(a); }
    int cols() const { return size(a[0]); }

    Matrix operator* (const Matrix& other) const {
        assert(cols() == other.rows());
        Matrix result(rows(), other.cols());
        rep(i, rows()) rep(k, cols()) rep(j, other.cols())
                    result.a[i][j] += a[i][k] * other.a[k][j];
        return result;
    }

    Matrix expoMultiply(num power, Matrix v) const {
        assert(rows() == cols() && v.cols() == rows());
        assert(power >= 0);
        for (Matrix m{*this}; power; power >>= 1, m *= m)
            if (power & 1)
                v *= m;
        return v;
    }

    Matrix operator^ (num power) const {
        return expoMultiply(power, Matrix(rows(), true));
    }

    Matrix& operator*= (const Matrix& other) { return *this = *this * other; }
    Matrix& operator^= (num power) { return *this = *this ^ power; }
};
