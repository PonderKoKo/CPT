#include "../macros.h"

/* Dijkstra's Algorithm for Single-Source shortest paths for nonnegative weights
 * Complexity: m log n
 */
#ifdef PBDS
#include <bits/extc++.h>
#endif
seq dijkstra(int source, const Table<pair<int,num>>& adj) {
	seq dist(size(adj), 18_e);
	dist[source] = 0;
#ifdef PBDS
	__gnu_pbds::priority_queue<pair<num,int>, greater<>> pq;
    vector<decltype(pq)::point_iterator> it(size(adj));
#else
	priority_queue<pair<num,int>,vector<pair<num,int>>,greater<>> pq;
#endif
	for (pq.push({0, source}); !empty(pq);) {
		auto [d, u] = pq.top();
		pq.pop();
		for (const auto& [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
#ifdef PBDS
                if (it[v] == end(pq))
                    it[v] = pq.push({dist[v], v});
                else
                    pq.modify(it[v], {dist[v], v});
#else
				pq.emplace(dist[v], v);
#endif
            }
        }
	}
	return dist;
}

seq denseDijkstra(int u, const Table<pair<int,num>>& adj) {
	seq dist(size(adj), -1);
	for (dist[u] = -18_e; dist[u] < -1; dist[u] += 18_e, u = min_element(all(dist)) - begin(dist))
		for (auto [v, w] : adj[u])
			if (dist[v] < 0)
				dist[v] = min(dist[v], dist[u] + w);
	return dist;
}

// l must be >= the largest edge weight and must be one less than a power of 2
// Complexity: O(n * l + m)
vector<int> shortDijkstra(int source, const Table<pair<int,int>>& adj, int l) {
    vector<int> dist(size(adj), 9_e);
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