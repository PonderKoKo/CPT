#include "../macros.h"

template<typename T, auto f>
struct SegTree {
    int n;
    vector<T> s;
    SegTree(const vector<T>& a) : n(size(a)), s(2 * n) {
        copy(all(a), begin(s) + n);
        for (int i = n; --i;)
            s[i] = f(s[2 * i], s[2 * i + 1]);
    }
    void update(int i, T x) {
        for (s[i += n] = x; i /= 2;)
            s[i] = f(s[2 * i], s[2 * i + 1]);
    }
    auto query(unsigned l, unsigned r, auto x) {
        int i;
        for (l += n, r += n; (l ^ r) >> (i = countr_zero(l)); l += 1 << i)
            x = f(x, s[l >> i]);
        while (i--)
            if (r >> i & 1)
                x = f(x, s[r >> i ^ 1]);
        return x;
    }
};

/*
 * int search(auto&& p, uint l, auto x) {
        for (l += n; p(f(x, s[l >>= countr_zero(l)]));)
            x = f(x, s[l++]);
        for (; l < n; l *= 2) if (p(f(x, s[l])))
            x = f(x, s[l++]);
        return l - n + 1;
    }
 */