#include "../macros.h"

/* Strongly Connected Components in Directed Graph in O(V + E)
 * Returns vector with mapping to components (1-indexed, maximum is number of components).
 * Component Indices are in Reverse Topological Order (only edges to smaller components)
 */
vector<int> scc(const Table<int>& adj) {
    vector<int> a(size(adj)), b{a}, z;
    int t{0}, c{0};
    function<int(int)> f = [&] (int u) {
        int d = b[u] = ++t;
        z.push_back(u);
        for (int v : adj[u])
            if (!a[v])
                d = min(d, b[v] ?: f(v));
        if (d == b[u] && ++c)
            while (!a[u])
                a[z.back()] = c, z.pop_back();
        return b[u] = d;
    };
    rep(u, size(adj))
    	a[u] || f(u);
    return a;
}
// https://judge.yosupo.jp/submission/244338
