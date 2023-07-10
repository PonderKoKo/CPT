#include "../macros.h"

/* Dijkstra's Algorithm for Single-Source shortest paths for nonnegative weights
 * Complexity: m log n
 */
#include <bits/extc++.h>
seq dijkstra(int source, const Table<pair<int,num>>& adj) {
	seq dist(size(adj), 18_e);
	dist[source] = 0;
	__gnu_pbds::priority_queue<pair<num,int>, greater<>> pq;
    vector<decltype(pq)::point_iterator> it(size(adj));
	for (pq.push({0, source}); !empty(pq);) {
		auto [d, u] = pq.top();
		pq.pop();
		for (const auto& [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (it[v] == end(pq))
                    it[v] = pq.push({dist[v], v});
                else
                    pq.modify(it[v], {dist[v], v});
            }
        }
	}
	return dist;
}