#include "../macros.h"

// Two-Edge-Connected components in O(n + m)
// Returns mapping node->component (1-indexed)
// Bridges are the edges connecting two components
vector<int> tec(const Table<int>& adj) {
	vector<int> a(size(adj)), b{a}, z;
    int t{0}, c{0};
    function<int(int,int)> f = [&] (int u, int up) {
    	b[u] = ++t;
        z.push_back(u);
        for (int v : adj[u])
            up += b[v] ? (b[u] > b[v]) - (b[u] < b[v]) : f(v, -1);
        if (!up && ++c)
            while (!a[u])
                a[z.back()] = c, z.pop_back();
        return up;
    };
    rep(u, ssize(adj))
    	a[u] || f(u, 0);
    return a;
}
// https://judge.yosupo.jp/submission/244334
// C++23: auto f = [&] (this auto&& f, int u, int up) -> int { (244336)
