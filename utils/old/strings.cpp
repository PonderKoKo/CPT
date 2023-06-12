#include "../macros.h"

pair<seq,Graph> cyclic_shifts(const string& s) {
    num n = ssize(s), logn = 64 - countl_zero(static_cast<unsigned long long>(n));
    seq order(n);
    iota(all(order), 0);
    sort(all(order), [&] (num i, num j) { return s[i] < s[j]; });
    Graph classes(logn+1, seq(n, 0));
    rep(i, n-1)
        classes[0][order[i+1]] = classes[0][order[i]] + (s[order[i]] != s[order[i+1]]);
    rep(k, logn) {
        seq second(order), count(n);
        for (num& x : second)
            x -= 1 << k, x += (x < 0) * n;
        reverse(all(second));
        for (num& x : classes[k])
            count[x]++;
        partial_sum(all(count), begin(count));
        for (num& x : second)
            order[--count[classes[k][x]]] = x;
        rep(i, n-1)
            classes[k+1][order[i+1]] = classes[k+1][order[i]] +
                                       (classes[k][order[i]] != classes[k][order[i+1]] ||
                                        classes[k][(order[i] + (1 << k)) % n] != classes[k][(order[i+1] + (1 << k)) % n]);
    }
    return make_pair(order, classes);
}

seq lcp_array(const string& s, const seq& order, const Graph& classes) {
    num n = ssize(s), logn = ssize(classes) - 1;
    seq lcp(n-1, 0);
    rep(i, n-1)
        for (num k = logn; k >= 0; k--)
            if (classes[k][(order[i]+lcp[i]) % n] == classes[k][(order[i+1]+lcp[i]) % n])
                lcp[i] += 1 << k;
    return lcp;
}

seq p_function(string s) {
    num n = ssize(s);
    seq p(n);
    for (num i = 1; i < n; i++) {
        num j = p[i-1];
        while (j > 0 && s[i] != s[j])
            j = p[j-1];
        if (s[i] == s[j])
            j++;
        p[i] = j;
    }
    return p;
}

seq z_function(string s) {
    num n = ssize(s);
    seq z(n);
    for (num i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}