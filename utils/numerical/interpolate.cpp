#include "../types/mint.cpp"

// Assuming a = [P(0), P(1), ..., P(n-1)], computes P(x) for the unique polynomial P of degree n - 1.
// Complexity: O(n + log mod)
mint interpolate(vector<mint> a, num x) {
    mint z = 1; rep(i, size(a)) z *= i + 1; z = !z;
    rep(i, size(a)) a[i] *= z *= size(a) - i, end(a)[~i] *= z;
    for (mint& q : a) q *= z, z *= x--;
    for (z = 1; mint& q : a | views::reverse) q *= z, z *= -++x;
    return reduce(all(a));
}

// Computes Sum_{i=0}^{n-1} i^p [with (0^0 = 1)]
// Complexity: O(p log p)
mint power_sum(num p, num n) {
    vector<mint> a(p + 2);
    rep(i, p + 1) a[i + 1] = a[i] + (mint(i) ^ p);
    return interpolate(a, n);
}
