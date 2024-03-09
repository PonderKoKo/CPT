#include "../macros.h"
// Untested
// Set true if we deal with edge weights. Then the top vertex in subtree / path queries will be excluded.
template<bool EDGES>
struct HeavyLight {
    vector<int> sz, in, nx, d, p;
    HeavyLight(Table<int> adj, int root = 0) : sz(size(adj), 1), in(size(sz)), nx(in), d(in) {
        int t = 0;
        dfs1(root, adj);
        dfs2(root, t, adj);
    }

    void dfs1(int u, Table<int>& adj) {
        for (int& v : adj[u]) {
            d[v] = d[u] + 1;
            p[v] = u;
            dfs1(v);
            sz[u] += sz[v];
            if (sz[v] > sz[adj[u][0]])
                swap(v, adj[u][0]);
        }
    }

    void dfs2(int u, int& t, const Table<int>& adj) {
        in[u] = t++;
        for (int v : adj[u]) {
            nx[v] = v == adj[u][0] ? nx[u] : v;
            dfs2(v, t, adj);
        }
    }

    int node(int u) { return in[u]; }
    pair<int,int> subtree(int u) { return {in[u] + EDGES, in[u] + sz[u]}; }
    vector<pair<int,int>> path(int u, int v) {
        vector<pair<int,int>> ans;
        for (; nx[u] != nx[v]; v = p[nx[v]]) {
            if (d[u] < d[v]) swap(u, v);
            ans.emplace_back(in[nx[u]], in[u] + 1);
        }
        if (d[u] < d[v]) swap(u, v);
        ans.emplace_back(in[v] + EDGES, in[u] + 1);
        return ans;
    }
};