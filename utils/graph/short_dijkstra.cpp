#include "../macros.h"

// Complexity: O(n * max{weights} + m)
auto short_dijkstra(int u, const Table<pair<int,int>>& adj) {
    int l = 1;
    for (auto& x: adj)
        for (auto [y, z] : x)
            while (l <= z)
                l *= 2;
    vector<int> d(size(adj), 1e9), p(d);
    Table<int> q(l--);
    d[u] = 0;
    q[0] = {u};
    rep(i, size(adj) * l) {
        rep(j, size(q[i & l]))
            if (d[u = q[i & l][j]] == i)
                for (auto [v, w] : adj[u])
                    if ((w += i) < d[v])
                        d[v] = w, p[v] = u, q[w & l].push_back(v);
        q[i & l].clear();
    }
    return pair(d, p);
}
