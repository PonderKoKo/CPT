#include "../macros.h"
#include "../data structures/UnionFind.cpp"
seq tarjanLCA(const Graph& adj, const vector<par>& queries) {
    num n = ssize(adj), q = ssize(queries);
    seq ancestor(n);
    vector<vector<par>> qadj(n);
    rep(i, q)
        qadj[queries[i].first].emplace_back(queries[i].second, i),
        qadj[queries[i].second].emplace_back(queries[i].first, i);
    vector<bool> visited(n);
    UnionFind uf(n);
    seq ans(q);
    function<void(num)> dfs = [&](num u) {
        visited[u] = true;
        ancestor[u] = u;
        for (num v : adj[u])
            if (!visited[v])
                dfs(v), uf.join(u, v), ancestor[uf.find(u)] = u;
        for (const auto& [v, i] : qadj[u])
            if (visited[v])
                ans[i] = ancestor[uf.find(v)];
    };
    dfs(0);
    return ans;
}

// Offline RMQ in O(alpha(n)) average with Arpa's Trick

class BinaryLifting {
    // Graph may be a forest, but queries must be in the same tree
    num n, logn;
    Graph ancestor, lift;
    seq depth;
    // Commutative, associative
    static const num neutral = numeric_limits<num>::min();
    static num f(num x, num y) {
        return max(x, y);
    }

    void dfs(num node, const Table<par>& adj) {
        for (auto [child, weight] : adj[node])
            if (depth[child] != -1)
                ancestor[child][0] = node,
                lift[child][0] = weight,
                depth[child] = depth[node] + 1,
                dfs(child, adj);
    }
public:
    explicit BinaryLifting(const Table<par>& adj) : n(ssize(adj)), logn(log2(n) + 1), ancestor(n, seq(logn)), lift(n, seq(logn)), depth(n, -1) {
        rep(i, n)
            if (depth[i] == -1)
                depth[i] = 0, ancestor[i][0] = i, dfs(i, adj);

        rep(j, logn - 1)
            rep(i, n)
                ancestor[i][j + 1] = ancestor[ancestor[i][j]][j],
                lift[i][j + 1] = f(lift[i][j], lift[ancestor[i][j]][j]);
    }

    num query(num u, num v) const {
        if (depth[u] < depth[v])
            swap(u, v);
        num ans = neutral;
        num diff = depth[u] - depth[v];
        rep(j, logn)
            if (diff & (1 << j))
                ans = f(ans, lift[u][j]),
                u = ancestor[u][j];
        if (u == v)
            return ans;
        for (num j = logn - 1; j >= 0; j--)
            if (ancestor[u][j] != ancestor[v][j])
                ans = f(ans, f(lift[u][j], lift[v][j])),
                u = ancestor[u][j],
                v = ancestor[v][j];
        return f(ans, f(lift[u][0], lift[v][0]));
    }
};