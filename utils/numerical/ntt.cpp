#include "../macros.h"
#include "../types/modular.cpp"

constexpr num m = 998244353;
using mod = modular<m>;
mod r = 3;
void ntt(auto& a) {
    num n = ssize(a), L = bit_width(size(a)) - 1;
    static vector<mod> rt(2, 1);
    for (static num k = 2; k < n; k *= 2) {
        rt.resize(n);
        auto z{r ^ m / 2 / k};
        rep(i, k)
            rt[i + k] = rt[(i + k) / 2] * (~i & 1 ?: z);
    }
    vector<int> rev(n);
    rep(i,n)
        rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,n)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            rep(j, k) {
                auto z = rt[j + k] * a[i + j + k];
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
        }
    }
}

vector<mod> convolve(vector<mod> a, vector<mod> b) {
    ull s = size(a) + size(b) - 1, n = 2 * bit_floor(s);
    vector<mod> out(n);
    a.resize(n), b.resize(n);
    ntt(a), ntt(b);
    auto inverse = !mod(n);
    rep(i, n)
        out[-i & (n - 1)] = a[i] * b[i] * inverse;
    ntt(out);
    return {begin(out), begin(out) + s};
}