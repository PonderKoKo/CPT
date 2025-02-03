#include "../macros.h"
#include "FenwickTree.cpp"

struct RangeFenwickTree {
    FenwickTree a, b;
    RangeFenwickTree(const seq& init) : a(init), b(size(init)) {}
    void add(int l, int r, num x) {
        a.add(l, -x * l), a.add(r, x * r);
        b.add(l, x), b.add(r, -x);
    }
    num sum(int l, int r) {
        return a.sum(l, r) + r * b.sum(r) - l * b.sum(l);
    }
};
