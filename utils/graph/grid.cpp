#include "../macros.h"

// Returns neighbors in flattened grid.
vector<int> neighbors(int u, int n, int m) {
	vector a{u + m, u - m, u - 1 - n * m * !(u % m), u + 1 + n * m * !((u + 1) % m)};
	erase_if(a, [&] (int x) { return x < 0 || x >= n * m;});
	return a;
}
