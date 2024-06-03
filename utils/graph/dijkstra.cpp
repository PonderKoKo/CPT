#include "../macros.h"

seq dijkstra(int s, const Table<pair<int,num>>& adj) {
	seq d(size(adj), 1e18);
	priority_queue<pair<num,int>,vector<pair<num,int>>,greater<>> pq;
	for (pq.emplace(d[s] = 0, s); !empty(pq);) {
		auto [du, u] = pq.top();
		pq.pop();
		if (du == d[u])
		    for (auto&& [v, w] : adj[u])
				if (d[u] + w < d[v])
				    pq.emplace(d[v] = d[u] + w, v);
	}
	return d;
}

seq denseDijkstra(int u, const Table<pair<int,num>>& adj) {
	seq dist(size(adj), -1);
	for (dist[u] = -1e18; dist[u] < -1; dist[u] += 1e18, u = min_element(all(dist)) - begin(dist))
		for (auto [v, w] : adj[u])
			if (dist[v] < 0)
				dist[v] = min(dist[v], dist[u] + w);
	return dist;
}

// l must be >= the largest edge weight and must be one less than a power of 2
// Complexity: O(n * l + m)
template<int l>
vector<int> shortDijkstra(int source, const Table<pair<int,int>>& adj) {
    vector<int> dist(size(adj), 1e9);
    dist[source] = 0;
    Table<int> pq(l+1);
    pq[0].push_back(source);
    for (int d = 0; d < ssize(adj) * l; pq[d++ & l].clear())
        rep(i, size(pq[d & l])) // Index-based iteration important since we might push back into same vector
            if (dist[pq[d & l][i]] == d)
                for (auto [v, w] : adj[pq[d & l][i]])
                    if (d + w < dist[v])
                        dist[v] = d + w, pq[d + w & l].push_back(v);
    return dist;
}