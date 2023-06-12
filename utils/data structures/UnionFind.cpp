#include "../macros.h"

struct UnionFind {
	vector<int> parent;
	UnionFind(int n) : parent(n, -1) {}

	int find(int x) {
		return parent[x] < 0 ? x : parent[x] = find(parent[x]);
	}

	bool join(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y)
			return false;
		if (parent[x] > parent[y])
			swap(x, y);
		parent[x] += parent[y];
		parent[y] = x;
		return true;
	}
};