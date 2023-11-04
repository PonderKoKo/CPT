#include "../macros.h"

// s[i] = Sum over j: s[i-j-1] * t[j]; {0,1}, {1, 1} for fib
num linearRecurrence(seq s, seq t, num k, num mod) {
    num n = ssize(t);
    auto combine = [&](seq a, seq b) {
        seq res(n * 2 + 1);
        rep(i,n+1)
            rep(j,n+1)
                res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
        for (num i = 2 * n; i > n; --i)
            rep(j,n)
                res[i - 1 - j] = (res[i - 1 - j] + res[i] * t[j]) % mod;
        res.resize(n + 1);
        return res;
    };
    seq pol(n + 1), e(pol);
    pol[0] = e[1] = 1;
    for (++k; k; k /= 2) {
        if (k & 1)
            pol = combine(pol, e);
        e = combine(e, e);
    }
    num res = 0;
    rep(i,n)
        res = (res + pol[i + 1] * s[i]) % mod;
    return res;
}