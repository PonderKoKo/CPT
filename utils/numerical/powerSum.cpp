#include "../macros.h"
#include "../types/modular.cpp"
using mod = modular<998244353>;

mod bernoulli(num n) {
    static vector<mod> a{1, mod(-1) / 2, 1};
    for (static num i = 2; i <= n; i++, a.push_back(1))
        rep(k, i)
            a.back() -= mod::binom(i, k) * a[k] / (i - k + 1);
    return a[n];
}

// computes 1^p + 2^p + ... + (n-1)^p
mod power_sum(num p, num n) {
    mod ans;
    rep(k, p + 1)
        ans += mod::binom(p, k) * bernoulli(p - k) * (mod(n) ^ k + 1) / (k + 1);
    return ans;
}