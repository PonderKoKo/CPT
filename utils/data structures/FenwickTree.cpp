#include "../macros.h"

struct FenwickTree {
    seq a;
    FenwickTree(auto&& b) : a(b) {
        rep(i, size(a))
            if ((i | i + 1) < size(a))
                a[i | i + 1] += a[i];
    }
    num sum(int r) {
        return r ? a[r - 1] + sum(r & r - 1) : 0;
    }
    void add(int i, num x) {
        while (i < size(a))
            a[i] += x, i |= i + 1;
    }
    num sum(int l, int r) { return sum(r) - sum(l); }
    int search(num x) { // -1 if x <= 0 and largest i in [0..n] with sum[0..i) < x otherwise.
        int i = -1;
        for (int z = bit_floor(size(a)); z; z /= 2)
            if (i + z < size(a) && a[i + z] < x)
                x -= a[i += z];
        return i + (0 < x);
    }
    void push_back(num x) {
        for (int j = 1; size(a) & j; j *= 2)
            x += a[size(a) ^ j];
        a.push_back(x);
    }
};
