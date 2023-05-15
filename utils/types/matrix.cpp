#include "../macros.h"

template<typename T>
struct Matrix {
    num rows, cols;
    Table<T> a;
    Matrix(const Table<T>& t) : rows{ssize(t)}, cols{ssize(t.front())}, a{t} {}
    Matrix(num r, num c) : rows{r}, cols{c}, a(r, vector<T>(c)) {}

    Matrix operator* (const Matrix& other) const {
        assert(cols == other.rows);
        Matrix result(rows, other.cols);
        rep(i, rows) rep(j, other.cols) rep(k, cols)
        result.a[i][j] += a[i][k] * other.a[k][j];
        return result;
    }

    vector<T> operator* (const vector<T>& vec) const {
        assert(cols == ssize(vec));
        vector<T> result(rows);
        rep(i, rows) rep(j, cols)
        result[i] += a[i][j] * vec[j];
        return result;
    }

    Matrix operator^ (num power) const {
        assert(rows == cols);
        assert(power >= 0);
        Matrix result(rows, cols);
        rep(i, rows)
            result.a[i][i] = 1;
        for (Matrix m{*this}; power; power >>= 1, m *= m)
            if (power & 1)
                result *= m;
        return result;
    }

    vector<T> expoMultiply(num power, vector<T> vec) const {
        assert(rows == cols);
        assert(power >= 0);
        for (Matrix m{*this}; power; power >>= 1, m *= m)
            if (power & 1)
                vec = m * vec;
        return vec;
    }

    Matrix& operator*= (const Matrix& other) { return *this = *this * other; }
    Matrix& operator^= (num power) { return *this = *this ^ power; }
};