#include "../macros.h"

/* Topological Sort on Directed Graph in O(V + E)
 * Edges only go from Left to Right
 * Replace Assertion to handle Cycles
 */
vector<int> topoSort(const Table<int>& adj) {
    int n = ssize(adj), i = 0;
    vector<int> in(n), topo(n, -1);
    for (const auto& row : adj)
        for (const auto& node : row)
            in[node]++;
    rep(j, n)
        if (!in[j])
            topo[i++] = j;
    for (const auto& node : topo) {
        assert(node != -1);
        for (num next : adj[node])
            if (!--in[next])
                topo[i++] = next;
    }
    return topo;
}