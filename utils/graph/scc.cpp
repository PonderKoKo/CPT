#include "../macros.h"

/* Strongly Connected Components in Directed Graph in O(V + E)
 * Returns vector with mapping to components (1-indexed, maximum is number of components).
 * Component Indices are in Reverse Topological Order (only edges to smaller components)
 */
vector<int> scc(const Table<int>& adj) {
    vector<int> a(size(adj)), b(a), z;
    int t{0}, c{0};
    function<int(int)> dfs = [&] (int u) {
        int d = b[u] = ++t;
        z.push_back(u);
        for (int v : adj[u])
            if (!a[v])
                d = min(d, b[v] ?: dfs(v));
        if (d == b[u] && ++c)
            while (!a[u])
                a[z.back()] = c, z.pop_back();
        return b[u] = d;
    };
    rep(u, size(adj)) if (!a[u]) dfs(u);
    return a;
}

// Build Condensation Graph in O(V + E log E)
Table<int> condense(const Table<int>& adj, const vector<int>& a) {
    Table<int> c(*max_element(all(a)));
    rep(u, size(adj)) for (int v : adj[u])
        if (a[u] != a[v])
            c[a[u] - 1].push_back(a[v] - 1);
    for (auto& r : c)
        sort(all(r)), r.erase(unique(all(r)), end(r));
    return c;
}
