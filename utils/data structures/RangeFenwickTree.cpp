#include "FenwickTree.cpp"

struct RangeFenwickTree {
    FenwickTree a, b = size(a.a);
    void add(int l, int r, num x) {
        a.add(l, -x * l), a.add(r, x * r);
        b.add(l, x), b.add(r, -x);
    }
    num sum(int l, int r) {
        return a.sum(l, r) + r * b.sum(r) - l * b.sum(l);
    }
    int search(num x) {
        num i = -1, y = 0;
        for (int z = bit_floor(size(a.a)); z; z /= 2)
            if (i + z < size(a.a) && a.a[i + z] + (i + z + 1) * (y + b.a[i + z]) < x)
                x -= a.a[i += z], y += b.a[i];
        return i + (0 < x);
    }
};
