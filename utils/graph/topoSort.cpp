#include "../macros.h"

/* Topological Sort on Directed Graph in O(V + E)
 * Edges only go from Left to Right
 * Replace Assertion to handle Cycles
 */
seq topoSort(const Graph& adj) {
    num n = ssize(adj), i = 0;
    seq in(n), topo(n, -1);
    for (const seq& row : adj)
        for (num node : row)
            in[node]++;
    rep(j, n)
        if (!in[j])
            topo[i++] = j;
    for (num node : topo) {
        assert(node != -1);
        for (num next : adj[node])
            if (--in[next])
                topo[i++] = next;
    }
    return topo;
}