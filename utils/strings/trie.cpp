#include "../macros.h"

template<int sigma = 26, int alpha = 'a'>
struct Trie {
	vector<array<int,sigma>> a{1};
	int nx(int v, int c) { return a[v][c] ?: a[v][c] = (a.emplace_back(), size(a) - 1); }
	int update(const auto& s, int v = 0) { for (auto&& x : s) v = nx(v, x - alpha); return v; }
};