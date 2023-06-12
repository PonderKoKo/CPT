#include "../macros.h"

/* Dijkstra's Algorithm for Single-Source shortest paths for nonnegative weights
 * Complexity: m log n
 */
seq dijkstra(num source, const Table<par>& adj) {
	seq dist(size(adj), 18_e);
	dist[source] = 0;
	priority_queue<par, vector<par>, greater<>> pq;
	for (pq.emplace(0, source); !empty(pq);) {
		auto [d, v] = pq.top();
		pq.pop();
		if (d != dist[v])
			continue;
		for (const auto& [to, weight] : adj[v])
			if (dist[v] + weight < dist[to])
				pq.emplace(dist[to] = dist[v] + weight, to);
	}
	return dist;
}

seq setDijkstra(num source, const Table<par>& adj) {
	seq dist(size(adj), 18_e);
	dist[source] = 0;
	auto cmp = [&] (num a, num b) { return par(dist[a], a) < par(dist[b], b); };
	set<num,decltype(cmp)> pq(cmp);
	for (pq.insert(source); !empty(pq);) {
		num v = *begin(pq);
		pq.erase(begin(pq));
		for (const auto& [to, weight] : adj[v])
			if (dist[v] + weight < dist[to])
				pq.erase(to), dist[to] = dist[v] + weight, pq.insert(to);
	}
	return dist;
}