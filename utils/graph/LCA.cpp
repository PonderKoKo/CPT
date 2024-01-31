#include "../macros.h"
#include "../data structures/SparseTable.cpp"

struct LCA {
	int t = 0;
	vector<int> d, o, r, q;
	OpSparseTable<int, greater<>> st;
	LCA(const vector<vector<int>>& adj, int root = 0) : d(size(adj)), q(d), st((dfs(0, -1, adj), r)) {}

	void dfs(int u, int p, const vector<vector<int>>& adj) {
		q[u] = t++;
		for (int v : adj[u])
			if (v != p)
				d[v] = d[u] + 1, o.push_back(u), r.push_back(q[u]), dfs(v, u, adj);
	}

	int query(int u, int v) const {
		if (u == v)
			return u;
		if (q[u] > q[v])
			swap(u, v);
		return o[st.query(q[u], q[v])];
	}

	int dist(int u, int v) const {
		return d[u] + d[v] - 2 * d[query(u, v)];
	}
};