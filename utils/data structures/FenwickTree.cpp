#include "../macros.h"

struct FenwickTree {
    seq a;
    FenwickTree(int n) : a(n) {}
    FenwickTree(const seq& init) : a(size(init)) {
        for (int i = 0; i < ssize(a); i++) {
            a[i] += init[i];
            if (int j = i | i + 1; j < ssize(a))
                a[j] += a[i];
        }
    }
    num query(int r) const {
        return r ? a[r - 1] + query(r & r - 1) : 0;
    }
    void update(int i, num x) {
        if (i < ssize(a)) a[i] += x, update(i | i + 1, x);
    }
    num query(int l, int r) const { return query(r) - query(l); }
    int search(num x) const { // Smallest i >= 0 s. t. sum[0, i] inclusive! is >= x, or n if never.
        int i = 0;
        for (int z = bit_floor(size(a)); z; z /= 2)
            if (i + z <= ssize(a) && a[i + z - 1] < x)
                x -= a[(i += z) - 1];
        return i;
    }
};
