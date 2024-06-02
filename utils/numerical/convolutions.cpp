#include "../macros.h"

template<auto t, auto it>
auto convolve(auto a, auto b) {
    a.resize(max(size(a), size(b))), b.resize(max(size(a), size(b)));
    t(a), t(b);
    rep(i, size(a)) a[i] *= b[i];
    return it(a), a;
}
// MAX convolve<[] (auto& a) { partial_sum(all(a), begin(a)); },[] (auto& a) { adjacent_difference(all(a), begin(a)); }>(a[0], a[1]);
// MIN convolve<[] (auto& a) { partial_sum(rbegin(a), rend(a), rbegin(a)); },[] (auto& a) { adjacent_difference(rbegin(a), rend(a), rbegin(a)); }>(a[0], a[1]);

template<int u, int v>
void wht(seq& a) {
    assert(has_single_bit(size(a)));
    for (int s = 1; s < ssize(a); s *= 2)
        rep(i, size(a)) if (i & s)
            tie(a[i - s], a[i]) = pair{a[i] + u * a[i - s], a[i - s] + v * a[i]};
}
// AND convolve<wht<0,1>,wht<-1,0>>
// OR convolve<wht<1,0>,wht<0,-1>>
// XOR convolve<wht<1,-1>,[](auto& a) { wht<1,-1>(a); for (auto& x : a) x /= size(a); }>

template<bool b>
void gcdt(seq& a) {
    rep(u, size(a)) {
        int i = b ? u : size(a) - u - 1;
        for (int j = 2 * i; j < ssize(a); j += i)
            a[i] += a[j] * (b ?: -1);
    }
}
// GCD convolve<gcdt<true>,gcdt<false>>
