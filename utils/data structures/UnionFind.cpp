#include "../macros.h"

struct UnionFind {
    vector<int> p;
    UnionFind(int n) : p(n, -1) {}
    int find(int x) {
        return p[x] < 0 ? x : p[x] = find(p[x]);
    }
    bool join(int x, int y) {
        while (p[x] > p[y = find(y)]) swap(x, y);
        return x != y && (p[x] += exchange(p[y], x));
    }
};
