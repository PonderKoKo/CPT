#include "../macros.h"

#include "../types/modular.cpp"

constexpr num module = 998'244'353;
using mod = modular<module>;
constexpr mod root = 3;
void ntt(vector<mod>& a) {
    num n = ssize(a), L = bit_width(size(a)) - 1;
    static vector<mod> rt(2, 1);
    for (static num k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);
        vector<mod> z{1, root ^ (module >> s)};
        for (num i = k; i < 2 * k; i++)
            rt[i] = rt[i / 2] * z[i & 1];
    }
    seq rev(n);
    rep(i,n)
        rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,n)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, k) {
                mod z = rt[j + k] * a[i + j + k], &ai = a[i + j];
                a[i + j + k] = ai - z + (z > ai ? module : 0);
                ai += (ai + z >= module ? z - module : z);
            }
}

vector<mod> convolve(const vector<mod> &a, const vector<mod> &b) {
    num s = ssize(a) + ssize(b) - 1;
    num n = 2 * bit_floor(static_cast<unsigned long long>(s));
    vector<mod> x(a), y(b), out(n);
    x.resize(n), y.resize(n);
    ntt(x), ntt(y);
    mod inverse = !mod(n);
    rep(i, n)
        out[-i & (n - 1)] = x[i] * y[i] * inverse;
    ntt(out);
    return {out.begin(), out.begin() + s};
}