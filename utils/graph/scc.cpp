#include "../macros.h"

/* Strongly Connected Components in Directed Graph in O(n + m)
 * Returns vector with mapping to components (0-indexed).
 * Component Indices are in Reverse Topological Order (only edges to smaller components)
 */
vector<int> scc(const Table<int>& adj) {
    int n = size(adj), t = 0, c = 0;
    vector<int> a(n), b(n), z(n);
    function<void(int)> f = [&] (int u) {
        if (b[u]) return;
        z[t] = u;
        b[u] = ++t;
        for (int v : adj[u])
            f(v), b[u] = min(b[u], b[v]);
        if (u == z[b[u] - 1] && --c) while (b[u] <= t)
            a[z[--t]] = ~c, b[z[t]] = 1e9;
    };
    rep(u, n) f(u);
    return a;
}
