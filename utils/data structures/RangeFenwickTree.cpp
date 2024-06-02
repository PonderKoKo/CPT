#include "../macros.h"
#include "FenwickTree.cpp"

struct RangeFenwickTree {
    FenwickTree a, b;
    RangeFenwickTree(const seq& init) : a(init), b(seq(size(init))) {}
    void update(int l, int r, num x) {
        a.update(l, -x * l), a.update(r, x * r);
        b.update(l, x), b.update(r, -x);
    }
    num query(int r) const { return a.query(r) + r * b.query(r); }
    num query(int l, int r) const { return query(r) - query(l); }
};