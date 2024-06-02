#include "../macros.h"
#include "../data structures/SparseTable.cpp"

struct LCA {
    int t = 0;
    vector<int> d, o, r, q;
    SparseTable<int,ranges::min> st;
    LCA(const Table<int>& adj, int root = 0) : d(size(adj)), q(d), st((dfs(root, -1, adj), r)) {}

    void dfs(int u, int p, const Table<int>& adj) {
        q[u] = t++;
        for (int v : adj[u])
            if (v != p)
                d[v] = d[u] + 1, o.push_back(u), r.push_back(q[u]), dfs(v, u, adj);
    }

    int query(int u, int v) const {
        if (u == v)
            return u;
        if (q[u] > q[v])
            swap(u, v);
        return o[st.query(q[u], q[v])];
    }

    int dist(int u, int v) const {
        return d[u] + d[v] - 2 * d[query(u, v)];
    }

    // Computes virtual tree in O(k log k).
    // Children are stored in aux (overwrites previous calls). Returns root of virtual tree.
   // Table<int> aux{Table<int>(size(d))};
   // int virtualTree(vector<int> a) {
   //     ranges::sort(a, {}, [&] (int x) { return q[x]; });
   //     for (int i = size(a); --i;) a.push_back(query(a[i - 1], a[i]));
   //     ranges::sort(a, {}, [&] (int x) { return q[x]; });
   //     a.erase(unique(all(a)), end(a));
   //     stack<int> s{{a[0]}};
   //     for (int x : a) {
   //         while (query(s.top(), x) != s.top())
   //             s.pop();
   //         aux[s.top()].push_back(x);
   //         aux[x].clear();
   //         s.push(x);
   //     }
   //     return a[0];
   // }
};