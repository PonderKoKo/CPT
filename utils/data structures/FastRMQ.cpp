#include "../macros.h"

// Construction O(n), Queries O(1)
// index returns largest index in [l..r) with minimum value. Change to less_equal for smallest index with min value
// greater / greater_equal give maximum.
template<typename T, auto c = less{}>
struct FastRMQ {
    vector<T> a;
    int n = size(a);
    vector<unsigned> m, t;
    int f(int i, int j) { return c(a[i], a[j]) ? i : j; }
    int q(int i) { return i + bit_width(m[i]); }
    FastRMQ(const vector<T>& a) : a(a), m(n), t(n) {
        for (int i = n - 1; i--;)
            for (m[i] = 2 * m[i + 1] + 1; m[i] && c(a[i], a[i + 1 + countr_zero(m[i])]); m[i] &= m[i] - 1);
        n /= 33;
        rep(i, n) t[i] = q(33 * i);
        rep(i, bit_width(n / 2u) * n)
            t[i + n] = f(t[i], t[i + (1 << i / n)]);
    }
    int index(int l, int r) {
        if (r - l < 33)
            return l + bit_width(m[l] & (1u << r - l - 1) - 1);
        if (r - l < 67)
            return f(q(l), q(r - 33));
        unsigned x = l / 33 + 1, y = r / 33, z = bit_width(y - x) - 1;
        return f(f(q(l), t[n * z + x]), f(t[n * z + y - (1 << z)], q(r - 33)));
    }
    T query(int l, int r) { return a[index(l, r)]; }
};
