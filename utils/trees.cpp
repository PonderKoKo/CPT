#include "macros.h"

struct SegTree {
    typedef num T;
    static constexpr T unit = numeric_limits<num>::max();
    static T f(T a, T b) {
        return min(a, b);
    }
    num n;
    vector<T> s;

    explicit SegTree(num size) : n(size), s(2*n, unit) {}
    void update(num pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(num l, num r) {
        T ra = unit, rb = unit;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2) ra = f(ra, s[l++]);
            if (r % 2) rb = f(s[--r], rb);
        }
        return f(ra, rb);
    }
    // All Following is Optional
    explicit SegTree(const vector<T>& a) : n(ssize(a)), s(2*n, unit) {
        rep(i, n)
            s[i + n] = a[i];
        for (num i = n - 1; i > 0; --i)
            s[i] = f(s[i * 2], s[i * 2 + 1]);
    }
    // Assuming p monotonic: Returns first r such that p(query(l, r)) is true or n+1 otherwise
    num search(num l, const function<bool(T)> p) {
        seq splits, splits_back;
        num r = n;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2) splits.push_back(l++);
            if (r % 2) splits_back.push_back(--r);
        }
        splits.insert(splits.end(), splits_back.rbegin(), splits_back.rend());
        T acc = unit;
        for (num i : splits) {
            if (p(f(acc, s[i]))) {
                while (i < n) {
                    if (p(f(acc, s[i*2])))
                        i *= 2;
                    else
                        acc = f(acc, s[i*2]), i = i*2 + 1;
                }
                return i - n + 1;
            }
            acc = f(acc, s[i]);
        }
        return n+1;
    }
};

class UpdateSegmentTree {
private:
    using T = num;
    using T_lazy = num;
    static constexpr T q_neutral = 0;
    static constexpr T_lazy u_neutral = 0;
    static T q_func(T a, T b) {
        return a + b;
    }
    static T u_func(T prev, num len, T_lazy upd) {
        return prev + len * upd;
    }
    static T_lazy l_func(T_lazy prev, T_lazy next) {
        return prev + next;
    }
    num n;
    vector<T> a;
    vector<T_lazy> lazy;
public:
    /* Naming scheme for parameters:
     * node is 1-based index of current node, [l, r) is the range of the current node
     * [ql, qr) is range of the query, qi is index of a query
     */
    explicit UpdateSegmentTree(const vector<T>& init) : n(ssize(init)), a(4 * n, q_neutral), lazy(4 * n, u_neutral) {
        build(init, 1, 0, n);
    }

    explicit UpdateSegmentTree(num size) : a(4 * size, q_neutral), lazy(4 * size, u_neutral), n(size) { }

    T build(const vector<T>& init, num node, num l, num r) {
        if (l + 1 == r)
            return a[node] = init[l];
        num mid = (l + r) / 2;
        return a[node] = q_func(build(init, node * 2, l, mid),
                                build(init, node * 2 + 1, mid, r));
    }

    T operator[] (num i) {
        return query(i, i + 1);
    }

    T query(num ql, num qr) {
        assert(/* l >= 0 && */ql <= qr && qr <= n);
        return query(1, 0, n, ql, qr);
    }

    T query(num node, num l, num r, num ql, num qr) {
        if (ql >= r || qr <= l) // [l, r) and [ql, qr) are disjoint
            return q_neutral;
        lazily(node, l, r);
        if (ql <= l && r <= qr) // [l, r) is a subset of [ql, qr)
            return a[node];
        num mid = (l + r) / 2;
        return q_func(query(node * 2, l, mid, ql, qr), query(node * 2 + 1, mid, r, ql, qr));
    }

    void update (num ql, num qr, T_lazy val) {
        assert(/* l >= 0 && */ql <= qr && qr <= n);
        update(1, 0, n, ql, qr, val);
    }

    T update (num node, num l, num r, num ql, num qr, T_lazy val) {
        lazily(node, l, r);
        if (ql >= r || qr <= l) // [l, r) and [ql, qr) are disjoint
            return a[node];
        if (ql <= l && r <= qr) { // [l, r) is a subset of [ql, qr)
            lazy[node] = val;
            return lazily(node, l, r);
        }
        num mid = (l + r) / 2;
        return a[node] = q_func(update(node * 2, l, mid, ql, qr, val),
                                update(node * 2 + 1, mid, r, ql, qr, val));
    }

    void set(num qi, T val) {
        assert(/* i >= 0 && */qi < n);
        set(1, 0, n, qi, val);
    }

    T set (num node, num l, num r, num qi, T val) {
        lazily(node, l, r);
        if (qi >= r || qi < l)
            return a[node];
        if (l + 1 == r)
            return a[node] = val;
        num mid = (l + r) / 2;
        return a[node] = q_func(set(node * 2, l, mid, qi, val), set(node * 2 + 1, mid, r, qi, val));
    }

    T lazily (num node, num l, num r) {
        if (lazy[node] == u_neutral)
            return a[node];
        a[node] = u_func(a[node], r - l, lazy[node]);
        if (l + 1 < r) {
            lazy[node * 2] = l_func(lazy[node * 2], lazy[node]);
            lazy[node * 2 + 1] = l_func(lazy[node * 2 + 1], lazy[node]);
        }
        lazy[node] = u_neutral;
        return a[node];
    }

    /* Assuming p: query([ql, x)) × interval_length -> bool is monotonic in x.
     * Returns the index of the first element x, such that query([ql, x)) is true.
     * If no such element exists, returns n + 1
     * Complexity is O(log n) rather than O((log n)^2) by just binary searching from the outside
     */
    num search(num ql, const function<bool(T, num)>& p) {
        T acc_val = q_neutral;
        num acc_len = 0;
        return search(1, 0, n, ql, n, acc_val, acc_len, p);
    }

    num search(num node, num l, num r, num ql, num qr, T& acc_val, num& acc_len, const function<bool(T, num)>& p) {
        if (r <= ql)
            return n + 1; // sentinel value
        if (l >= qr)
            return l; // Why isn't this r?
        lazily(node, l, r);
        if (l >= ql && r <= qr && !p(q_func(acc_val, a[node]), acc_len + r - l)) {
            acc_val = q_func(acc_val, a[node]);
            acc_len += r - l;
            return n + 1;
        }
        if (l + 1 == r)
            return l; // Why isn't this r?

        num mid = (l + r) / 2;
        num res = search(node * 2, l, mid, ql, qr, acc_val, acc_len, p);
        if (res != n + 1)
            return res;
        return search(node * 2 + 1, mid, r, ql, qr, acc_val, acc_len, p);
    }
};

struct UnionFind {
    vector<int> parent;
    UnionFind(int n) : parent(n, -1) {}

    int find(num x) {
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
                dfs(v), uf.merge(u, v), ancestor[uf.find(u)] = u;
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
    using WGraph = vector<vector<par>>;
    num n, logn;
    Graph ancestor, lift;
    seq depth;
    // Commutative, associative
    static const num neutral = numeric_limits<num>::min();
    static num f(num x, num y) {
        return max(x, y);
    }

    void dfs(num node, const WGraph& adj) {
        for (auto [child, weight] : adj[node])
            if (depth[child] != -1)
                ancestor[child][0] = node,
                lift[child][0] = weight,
                depth[child] = depth[node] + 1,
                dfs(child, adj);
    }
public:
    explicit BinaryLifting(const WGraph& adj) : n(ssize(adj)), logn(log2(n) + 1), ancestor(n, seq(logn)), lift(n, seq(logn)), depth(n, -1) {
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