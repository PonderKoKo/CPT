#include "../macros.h"

template<typename T, auto f>
struct SegmentTree {
    int n; vector<T> s;
    SegmentTree(const vector<T>& a) : n(size(a)), s(2 * n) {
        copy(all(a), begin(s) + n);
        for (int i = n; --i;)
            s[i] = f(s[2 * i], s[2 * i + 1]);
    }
    void update(int i, T x) {
        for (s[i += n] = x; i /= 2;)
            s[i] = f(s[2 * i], s[2 * i + 1]);
    }
    T query(int l, int r) {
        u_int q = l + n, i = min(q & -q, bit_floor(r - l + 0u));
        return l + i < r ? f(s[q / i], query(l + i, r)) : s[q / i];
    }
};
