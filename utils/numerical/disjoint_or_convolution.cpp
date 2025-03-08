#include "convolutions.cpp"

// ans[i] = sum_(j, k | j & k = 0 and j | k = i) a[j] * b[k]. Untested
template<typename T>
vector<T> disjoint_or_convolve(vector<T> a, const vector<T>& b) {
    int n = bit_width(size(a));
    vector aa(n, vector<T>(1 << n - 1)), bb(aa), cc(aa);
    rep(i, 1 << n - 1)
        aa[popcount(ull(i))][i] = a[i], bb[popcount(ull(i))][i] = b[i];
    for (auto& x : views::join(array{aa, bb}))
        OR<1>(x);
    rep(i, n) rep(j, i + 1) rep(x, 1 << n - 1)
                cc[i][x] += aa[j][x] * bb[i - j][x];
    for (auto& x : cc) OR<0>(x);
    rep(i, 1 << n - 1) a[i] = cc[popcount(ull(i))][i];
    return a;
}
