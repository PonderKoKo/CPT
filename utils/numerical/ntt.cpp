#include "../macros.h"
#include "../types/mint.cpp"

vector<mint> convolve(vector<mint> a, vector<mint> b) {
    assert(mod == 998244353);
    static vector<mint> rt(2, 1);

    ull s = size(a) + size(b) - 1, n = 2 * bit_floor(s);
    mint inverse = !mint(n);
    for (static int k = 2; k < n; k *= 2) {
        rt.resize(n);
        mint z = 3; // !
        z ^= mod / 2 / k;
        rep(i, k)
            rt[i + k] = rt[(i + k) / 2] * (~i & 1 ?: z);
    }

    vector<int> rev(n);
    rep(i, n) rev[i] = (rev[i / 2] | (i & 1) * n) / 2;
    auto ntt = [&] (vector<mint>& a) {
        rep(i, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2) {
            for (int i = 0; i < n; i += 2 * k) {
                rep(j, k) {
                    mint z = rt[j + k] * a[i + j + k];
                    a[i + j + k] = a[i + j] - z;
                    a[i + j] += z;
                }
            }
        }
    };
    vector<mint> out(n);
    a.resize(n), b.resize(n);
    ntt(a), ntt(b);
    rep(i, n)
        out[-i & n - 1] = a[i] * b[i] * inverse;
    ntt(out);
    return {begin(out), begin(out) + s};
}
