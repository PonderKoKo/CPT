#include "../macros.h"
// Euler's totient/phi function.
// Counts x in [1, n] s.t. gcd(x, n) = 1. So coprime integers. phi(1)=1
auto phi(int n) {
    vector<int> ans(n);
    rep(i, n) ans[i] = i >> (~i & 1);
    for (int i = 3; i < n; i += 2)
        if (ans[i] == i)
            for (int j = i; j < n; j += i)
                ans[j] -= ans[j] / i;
    return ans;
}
