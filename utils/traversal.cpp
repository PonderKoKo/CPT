#include "macros.h"

void bfs(u32 source, vector<vector<u32>>& adj, u32 n /* vertices */) {
    queue<u32> q;
    q.push(source);
    vector<i32> dist(n, -1);
    dist[source] = 0;
    while (!q.empty()) {
        u32 u = q.front();
        q.pop();
        for (u32 v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

void dfs(u32 source, vector<vector<u32>>& adj, vector<bool>& visited /* false initialized */) {
    // Do something
    visited[source] = true;
    for (u32 v : adj[source]) {
        if (!visited[v])
            dfs(v, adj, visited);
    }
}

// Unrooted, undirected
void treeDFS(u32 node, u32 parent /* pass as source for root */, vector<vector<u32>>& adj /*, dp-array */) {
    // Pre-order
    for (u32 v : adj[node]) {
        if (v != parent) {
            treeDFS(v, node, adj /*, dp-array */);
        }
    }
    // Post-order
}

// Rooted and directed
void treeDFS(u32 node, vector<vector<u32>>& children /*, dp-array */) {
    // Pre-order
    for (u32 v : children[node]) {
        treeDFS(v, children /*, dp-array */);
    }
    // Post-order
}

vector<u32> topo_sort (vector<vector<u32>>& adj /* directed */, u32 n /* vertices */) {
    vector<u32> in_degree(n, 0);
    for (const auto &v : adj)
        for (const auto u : v)
            in_degree[u]++;
    vector<u32> res;
    rep(i,n)
        if (!in_degree[i])
            res.push_back(i);
    rep(i,n)
        for (u32 v : adj[res[i]])
            if (!--in_degree[v])
                res.push_back(v);
    return res;
}