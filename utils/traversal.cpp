#include "macros.h"

void bfs(u32 source, const Graph& adj, u32 n) {
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

/*
 * visited should be false-initialized
 */
void dfs(u32 source, const Graph& adj, vector<bool>& visited) {
    // Do something
    visited[source] = true;
    for (u32 v : adj[source]) {
        if (!visited[v])
            dfs(v, adj, visited);
    }
}

// Unrooted, undirected
void treeDFS(u32 node, u32 parent, const Graph& adj) {
    // Pre-order
    for (u32 v : adj[node]) {
        if (v != parent) {
            treeDFS(v, node, adj);
        }
    }
    // Post-order
}

// Rooted and directed
void treeDFS(u32 node, const Graph& children) {
    // Pre-order
    for (u32 v : children[node]) {
        treeDFS(v, children);
    }
    // Post-order
}


vector<u32> topo_sort (const Graph& adj) {
    vector<u32> in_degree(adj.size(), 0);
    for (const auto &v : adj)
        for (const auto u : v)
            in_degree[u]++;
    vector<u32> res;
    rep(i,adj.size())
        if (!in_degree[i])
            res.push_back(i);
    rep(i,adj.size())
        for (u32 v : adj[res[i]])
            if (!--in_degree[v])
                res.push_back(v);
    return res;
}

/* Dinic's algorithm for Max Flow
 * Complexity: O(|V|^2 * |E|)
 */
template <typename flow_type>
class dinic {
    struct edge {
        size_t src, dst, rev;
        flow_type flow, cap;
    };

    int n;
    vector<vector<edge>> adj;

    explicit dinic(int n) : n(n), adj(n), level(n), q(n), it(n) {}

    void add_edge(size_t src, size_t dst, flow_type cap, flow_type rcap = 0) {
        adj[src].push_back({src, dst, adj[dst].size(), 0, cap});
        if (src == dst)
            adj[src].back().rev++;
        adj[dst].push_back({dst, src, adj[src].size() - 1, 0, rcap});
    }

    vector<int> level, q, it;

    bool bfs(int source, int sink) {
        fill(level.begin(), level.end(), -1);
        for (int qf = level[q[0] = sink] = 0, qb = 1; qf < qb; ++qf) {
            sink = q[qf];
            for (edge &e : adj[sink]) {
                edge &r = adj[e.dst][e.rev];
                if (r.flow < r.cap && level[e.dst] == -1)
                    level[q[qb++] = e.dst] = 1 + level[sink];
            }
        }
        return level[source] != -1;
    }

    flow_type augment(int source, int sink, flow_type flow) {
        if (source == sink)
            return flow;
        for (; it[source] != adj[source].size(); ++it[source]) {
            edge &e = adj[source][it[source]];
            if (e.flow < e.cap && level[e.dst] + 1 == level[source]) {
                flow_type delta = augment(e.dst, sink, min(flow, e.cap - e.flow));
                if (delta > 0) {
                    e.flow += delta;
                    adj[e.dst][e.rev].flow -= delta;
                    return delta;
                }
            }
        }
        return 0;
    }

    flow_type max_flow(int source, int sink) {
        for (vector<edge>& u : adj)
            for (edge& e : u)
                e.flow = 0;
        flow_type flow = 0;
        flow_type oo = numeric_limits<flow_type>::max();

        while (bfs(source, sink)) {
            fill(it.begin(), it.end(), 0);
            for (flow_type f; (f = augment(source, sink, oo)) > 0;)
                flow += f;

        } // level[u] = -1 => source side of min cut
        return flow;
    }
};