#include "../macros.h"

auto dijkstra(int s, const Table<pair<int,num>>& adj) {
	seq d(size(adj), 1e18);
	vector<int> p(size(adj), -1);
	priority_queue<pair<num,int>> q;
	for (q.emplace(d[s] = 0, s); !empty(q);) {
		auto [x, u] = q.top();
		q.pop();
		if (-x == d[u])
		    for (auto [v, w] : adj[u])
				if ((w -= x) < d[v])
				    p[v] = u, d[v] = w, q.emplace(-w, v);
	}
	return pair(d, p);
}
