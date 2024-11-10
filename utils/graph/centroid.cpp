#include "../macros.h"

void centroid(const vector<vector<int>>& a, auto &&f) {
	vector<int> s(size(a), 1), p(size(a), -1), q(size(a));
	for (int qn = 1; int u : q)
		for (int v : a[u])
			if (v != p[u])
				p[q[qn++] = v] = u;
	for (int i = size(a); --i;)
		s[p[q[i]]] += s[q[i]];
	vector<vector<int>> b(size(a));
	function<void(int,int)> dfs = [&] (int u, int p) {
		for (int v : a[u])
			if (v != p && s[v] > s[u] / 2)
				return s[u] -= exchange(s[v], s[u]), dfs(v, p);
		s[u] = 0;
		for (int v : a[u])
			if (s[v])
				dfs(v, u), b[u].push_back(v), b[v].push_back(u);
		f(b, u, p);
	};
	dfs(0, -1);
}
