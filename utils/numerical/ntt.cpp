#include "../macros.h"
#include "../types/mint.cpp"

template<num m, num r>
void ntt(vector<mint<m>>& a) {
    num n = ssize(a), L = bit_width(size(a)) - 1;
    static vector<mint<m>> rt(2, 1);
    for (static int k = 2; k < n; k *= 2) {
        rt.resize(n);
        auto z{mint<m>{r} ^ m / 2 / k};
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

template<num r = 3, num m = 998244353>
vector<mint<m>> convolve(vector<mint<m>> a, vector<mint<m>> b) {
    ull s = size(a) + size(b) - 1, n = 2 * bit_floor(s);
    auto inverse = !mint<m>(n);
    vector<mint<m>> out(n);
    a.resize(n), b.resize(n);
    ntt<r,m>(a), ntt<r,m>(b);
    rep(i, n)
        out[-i & (n - 1)] = a[i] * b[i] * inverse;
    ntt<r,m>(out);
    return {begin(out), begin(out) + s};
}
// https://judge.yosupo.jp/submission/244769
