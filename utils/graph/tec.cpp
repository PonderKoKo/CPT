#include "../macros.h"

// Two-Edge-Connected components in O(n + m)
// Returns mapping node->component (0-indexed).
// Bridges are the edges connecting two components.
// adj must be symmetric. Multi-edges and self-loops are handled.
vector<int> tec(const Table<int>& adj) {
    int n = size(adj), t = 0;
	vector<int> a(n), b(n), z(n + 1);
    function<int(int,int)> f = [&] (int u, int x) {
        if (b[u]) return (0 < x) - (x < 0);
        z[b[u] = ++t] = u;
        x = !x - 1;
        for (int v : adj[u])
            x += f(v, b[u] - b[v]);
        while (!x && ++z[0] && b[u] <= t)
            a[z[t--]] = --z[0];
        return x;
    };
    rep(u, n) f(u, 0);
    return a;
}
// https://judge.yosupo.jp/submission/252571
