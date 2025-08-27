#include "../macros.h"

struct ColorUnionFind {
    vector<int> p, c;
    ColorUnionFind(int n) : p(n, -1), c(n) {}
    int find(int x) {
        int q = p[x];
        return q < 0 ? x : (p[x] = find(q), c[x] ^= c[q], p[x]);
    }
    // Returns -1 for new connection, 0 for redundant join, >0 for contradictory join
    int join(int x, int y, int z) {
        int a = find(x), b = find(y);
        z ^= c[x] ^ c[y];
        if (a == b)
            return z;
        if (p[a] > p[b])
            swap(a, b);
        p[a] += p[b];
        p[b] = a;
        c[b] = z;
        return -1;
    }
};