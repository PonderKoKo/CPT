#include "../macros.h"

// Complexity: O(n^2 + m)
auto dense_dijkstra(int u, const Table<pair<int,num>>& adj) {
    seq d(size(adj), -1), p(d);
    for (d[u] = -1e18; d[u] < -1; d[u] += 1e18, u = min_element(all(d)) - begin(d))
        for (auto [v, w] : adj[u])
            if (d[v] < 0 && (w += d[u]) < d[v])
                d[v] = w, p[v] = u;
    return pair(d, p);
}
