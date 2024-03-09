#include "../macros.h"

struct UnionFind {
	vector<int> p;
	UnionFind(int n) : p(n, -1) {}

	int find(int x) {
		return p[x] < 0 ? x : p[x] = find(p[x]);
	}

	bool join(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y)
			return false;
		if (p[x] > p[y])
			swap(x, y);
		p[x] += p[y];
		p[y] = x;
		return true;
	}
};

struct ColorUnionFind {
    vector<int> p;
    vector<bool> c;
    ColorUnionFind(int n) : p(n, -1), c(n, false) {}

    pair<int,bool> find(int x) {
        if (p[x] < 0)
            return {x, false};
        auto [y, z] = find(p[x]);
        return {p[x] = y, c[x] = c[x] ^ z};
    }

    // Adds an edge between x and y so that c[x] ^ c[y] = z unless the graph would become uncolorable.
    // Returns true if the edge was added.
    bool join(int x, int y, bool z) {
        auto [u, a] = find(x);
        auto [v, b] = find(y);
        if (u == v)
            return (a ^ b) == z;
        if (p[u] > p[v])
            swap(u, v), swap(a, b);
        p[u] += p[v];
        p[u] = v;
        c[u] = a ^ b ^ z;
        return true;
    }
};

#include "Rollback.cpp"

struct UnionFindR {
    Rollback r;
    seq p;
    UnionFindR(int n) : p(n, -1) {}
    int find(int x) {
        return p[x] < 0 ? x : find(p[x]);
    }

    bool join(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        if (p[x] > p[y])
            swap(x, y);
        r.save(&p[x]);
        r.save(&p[y]);
        p[x] += p[y];
        p[y] = x;
        return true;
    }
};
