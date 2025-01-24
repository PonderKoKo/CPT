#include "../macros.h"

template<typename T, auto f = ranges::min>
struct SparseTable {
    Table<T> a;
    SparseTable(const vector<T>& x) : a(bit_width(size(x)), x) {
        rep(i, size(a) - 1)
            transform(begin(a[i]) + (1 << i), end(a[i]), begin(a[i]), begin(a[i + 1]), f);
    }
    T query(u_int l, u_int r) const {
        int t = bit_width(r - l) - 1;
        return f(a[t][l], a[t][r - (1 << t)]);
    }
};
