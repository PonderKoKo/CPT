#include "../macros.h"

struct UnionFind {
    vector<int> parent;
    UnionFind(int n) : parent(n, -1) {}

    int find(int x) {
        return parent[x] < 0 ? x : parent[x] = find(parent[x]);
    }

    bool join(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;
        if (parent[x] > parent[y])
            swap(x, y);
        parent[x] += parent[y];
        parent[y] = x;
        return true;
    }
};

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

tuple<seq,seq,seq> euler_tour(num root, const Graph& adj) {
    const num n = ssize(adj);
    seq first(n), depth(n), euler(2 * n - 1);
    num t = 0;
    function<void(num,num)> dfs = [&](num node, num parent) {
        euler[t] = node, first[node] = t++, depth[node] = depth[parent] + 1;
        for (num child : adj[node])
            if (child != parent)
                dfs(child, node), euler[t++] = node;
    };
    dfs(root, root);
    return make_tuple(euler, first, depth);
}

class LCASparseTable {
    num n;
    Graph table;
    seq first, depth;
    static num log2(num x) {
        return __builtin_clzll(1) - __builtin_clzll(x);
    }
    num f(num x, num y) const {
        return depth[x] < depth[y] ? x : y;
    }
    num query(num l, num r) const {
        num k = log2(r - l);
        return f(table[k][l], table[k][r - (1 << k)]);
    }
public:
    explicit LCASparseTable(const seq& euler, const seq& first_, const seq& depth_) : n(size(euler)), first(first_), depth(depth_) {
        table.emplace_back(euler);
        for (num k = 1; (1 << k) <= n; k++) {
            table.emplace_back(n - (1 << k) + 1);
            rep(i, n - (1 << k) + 1)
                table[k][i] = f(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }

    num lca(num u, num v) const {
        if (first[u] > first[v])
            swap(u, v);
        return query(first[u], first[v] + 1);
    }

    num dist(num u, num v) const {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }
};

LCASparseTable sparseLCA(num root, const Graph& adj) {
    const auto [euler, first, depth] = euler_tour(root, adj);
    return LCASparseTable(euler, first, depth);
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