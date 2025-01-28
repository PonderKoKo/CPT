#include "../macros.h"

// Requires symmetric adjacency list without multi-edges
template<class T>
vector<T> reroot(Table<int> adj, vector<T> a, auto&& f) {
    Table<T> b(size(a));
    [&] (this auto&& dfs, int u) -> void {
        for (int v : adj[u]) {
            erase(adj[v], u);
            dfs(v);
            b[u].push_back(accumulate(all(b[v]), a[v], f));
        }
    } (0);
    [&] (this auto&& dfs, int u, T p, auto l, auto r) -> void {
        if (l == r)
            a[u] = p;
        else {
            auto m = l + (r - l) / 2;
            dfs(u, accumulate(m, r, p, f), l, m);
            int v = adj[u][l - begin(b[u])];
            if (l == m)
                dfs(v, f(a[v], p), all(b[v]));
            else
                dfs(u, accumulate(l, m, p, f), m, r);
        }
    } (0, a[0], all(b[0]));
    return a;
}

// https://codeforces.com/contest/2050/submission/297105431