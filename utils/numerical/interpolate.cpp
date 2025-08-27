#include "../types/mint.cpp"

// Given a = [P(0), P(1), ..., P(n-1)], computes P(x) for the unique polynomial P of degree n - 1.
// Complexity: O(n + log mod)
// Works for T in {mint, double}
// x is num to use ++ and --, semantically should be T
template<typename T = mint>
T interpolate(vector<T> a, num x) {
    T z = 1; rep(i, size(a)) z *= i + 1; z = 1 / z;
    rep(i, size(a)) a[i] *= z *= size(a) - i, end(a)[~i] *= z;
    for (T& q : a) q *= z, z *= x--;
    for (z = 1; T& q : a | views::reverse) q *= z, z *= -++x;
    return reduce(all(a));
}

// Given P(x_i) = y_i for i in [0..n), computes P(z) for the unique polynomial P of degree n - 1.
// Complexity: O(n^2 * inv). Could be improved to O(n * (n + inv))
// Works for T in {mint, double, frac}.
// x's should be distinct.
template<typename T = mint>
T interpolate(const vector<T>& x, vector<T> y, T z) {
    rep(i, size(x)) for (T j : x) if (x[i] != j)
        y[i] *= (z - j) / (x[i] - j);
    return reduce(all(y));
}

// Computes Sum_{i=0}^{n-1} i^p [with 0^0 = 1]
// Complexity: O(p log p)
mint power_sum(num p, num n) {
    vector<mint> a(p + 2);
    rep(i, p + 1) a[i + 1] = a[i] + (mint(i) ^ p);
    return interpolate(a, n);
}
