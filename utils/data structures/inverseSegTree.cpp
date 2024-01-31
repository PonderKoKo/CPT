#include "../macros.h"

struct InverseSegTree {
    using T = num;
    // Associative and Commutative
    static constexpr auto f = plus<>();
    num n;
    vector<T> s;
    InverseSegTree(num size) : n(size), s(2*n) {}

    T operator[](num pos) {
        T res = s[pos += n];
        while (pos /= 2)
            res = f(res, s[pos]);
        return res;
    }
    void update(num l, num r, T val) {
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1)
                s[l] = f(val, s[l]), l++;
            if (r & 1)
                --r, s[r] = f(val, s[r]);
        }
    }
};