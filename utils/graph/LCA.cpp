#include "../data structures/SparseTable.cpp"

struct LCA {
    vector<int> d, o, r, q = d;
    SparseTable<int,ranges::min> st;
    LCA(const Table<int>& adj, int root = 0) : d(size(adj)), st((dfs(root, adj), r)) {}
    void dfs(int u, const Table<int>& adj) {
        q[u] = size(o);
        d[u]++;
        for (int v : adj[u])
            if (!d[v])
                d[v] = d[u], o.push_back(u), r.push_back(q[u]), dfs(v, adj);
    }

    int query(int u, int v) {
        if ((u ^ v) <= 0)
            return u & v;
        tie(u, v) = minmax(q[u], q[v]);
        return o[st.query(u, v)];
    }

    int dist(int u, int v) {
        return d[u] + d[v] - 2 * d[query(u, v)];
    }

    // Computes virtual tree in O(k log k).
    // Children are stored in adj (overwrites previous calls). Returns root of virtual tree.
    int virtual_tree(vector<int> a, Table<int>& adj) {
        rep(k, 2) {
            rep(i, k * size(a) / 2)
                a.push_back(query(a[i], a[i + 1]));
            ranges::sort(a, {}, [&] (int x) { return q[x]; });
        }
        for (stack<int> s{{a[0]}}; int x : a) {
            while (query(s.top(), x) != s.top())
                s.pop();
            adj[s.top()].push_back(x);
            adj[x].clear();
            s.push(x);
        }
        return a[0];
    }
};
