#include "../macros.h"
// Potentially broken?
template<class T>
vector<T> reroot(Table<int> adj, vector<T> a, auto&& f) {
	Table<T> b(size(a));
	auto dfs1 = [&] (auto&& dfs, int u, int p) -> T {
		adj[u].erase(remove(all(adj[u]), p), end(adj[u]));
		for (int v : adj[u])
			b[u].push_back(dfs(dfs, v, u));
		return accumulate(all(b[u]), a[u], f);
	};
	dfs1(dfs1, 0, -1);
	auto dfs2 = [&] (auto&& dfs, int u, T p, auto l, auto r) -> void {
		if (l == r)
			a[u] = p;
		else {
			auto m = l + (r - l) / 2;
			dfs(dfs, u, accumulate(m, r, p, f), l, m);
			int v = adj[u][l - begin(b[u])];
			if (l == m)
				dfs(dfs, v, f(a[v], p), all(b[v]));
			else
				dfs(dfs, u, accumulate(l, m, p, f), m, r);
		}
	};
	dfs2(dfs2, 0, a[0], all(b[0]));
	return a;
}