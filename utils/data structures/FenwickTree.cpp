#include "../macros.h"

struct FenwickTree {
    seq a;
    FenwickTree(int n) : a(n) {}
    FenwickTree(const seq& init) : FenwickTree(size(init)) {
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

struct RangeFenwickTree {
    FenwickTree a, b;
    RangeFenwickTree(int n) : a(n), b(n) {}
    RangeFenwickTree(const seq& init) : a(init), b(size(init)) {}
    void update(int l, int r, num x) {
        a.update(l, -x * l), a.update(r, x * r);
        b.update(l, x), b.update(r, -x);
    }
    num query(int r) const { return a.query(r) + r * b.query(r); }
    num query(int l, int r) const { return query(r) - query(l); }
};