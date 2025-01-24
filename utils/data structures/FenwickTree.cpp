#include "../macros.h"

struct FenwickTree {
    seq a;
    FenwickTree(int n) : a(n) {}
    FenwickTree(const seq& b) : a(b) {
        rep(i, size(a))
            if ((i | i + 1) < size(a))
                a[i | i + 1] += a[i];
    }
    num sum(int r) const {
        return r ? a[r - 1] + sum(r & r - 1) : 0;
    }
    void add(int i, num x) {
        if (i < size(a)) a[i] += x, add(i | i + 1, x);
    }
    num sum(int l, int r) const { return sum(r) - sum(l); }
    int search(num x) const { // -1 if x <= 0 and largest i in [0..n] with sum[0..i) < x otherwise.
        int i = -1;
        for (int z = bit_floor(size(a)); z; z /= 2)
            if (i + z < ssize(a) && a[i + z] < x)
                x -= a[i += z];
        return i + (0 < x);
    }
};
