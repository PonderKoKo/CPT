#include "../macros.h"

auto bfs(int u, const Table<int>& adj) {
    vector<int> d(size(adj), -1), p(d);
    for (queue<int> q{{u}}; !empty(q); q.pop())
        for (d[u = q.front()]++; int v : adj[u])
            if (d[v] < 0)
                p[v] = u, d[v] = d[u], q.push(v);
    return pair(d, p);
}
