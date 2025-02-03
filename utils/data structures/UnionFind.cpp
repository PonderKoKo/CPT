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
			return 0;
		if (p[x] > p[y])
			swap(x, y);
		p[x] += p[y];
		p[y] = x;
		return 1;
	}
};
