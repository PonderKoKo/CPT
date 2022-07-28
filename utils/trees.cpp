#include "macros.h"

// gcd works properly for unsigned ints since gcd(x, 0) = x for all x >= 0.
template<typename T, T neutral, T f(T,T)>
class SegmentTree {
private:
    vector<T> a;
    u32 n;
public:
    explicit SegmentTree(const vector<T>& init) : a(4 * init.size(), neutral /* necessary? */), n(init.size()) {
        build(init, 1, 0, n);
    }

    explicit SegmentTree(u32 size) : a(4 * size, neutral /* necessary? */), n(size) {
        vector<T> init(size, neutral);
        build(init, 1, 0, n);
    }

    const T& build(const vector<T>& init, u32 node, u32 l, u32 r) {
        if (l + 1 == r)
            return a[node] = init[l];
        u32 mid = (l + r) / 2;
        return a[node] = f(build(init, node * 2, l, mid),
                           build(init, node * 2 + 1, mid, r));
    }

    T operator[] (u32 i) const {
        return query(i, i + 1);
    }

    [[nodiscard]] T query(u32 l, u32 r) const {
        assert(/* l >= 0 && */l <= r && r <= n);
        return query(1, 0, n, l, r);
    }

    [[nodiscard]] T query(u32 node, u32 l, u32 r, u32 ql, u32 qr) const {
        if (ql >= r || qr <= l) // [l, r) and [ql, qr) are disjoint
            return neutral;
        if (ql <= l && r <= qr) // [l, r) is a subset of [ql, qr)
            return a[node];
        u32 mid = (l + r) / 2;
        return f(query(node * 2, l, mid, ql, qr), query(node * 2 + 1, mid, r, ql, qr));
    }

    void set(u32 i, T val) {
        assert(/* i >= 0 && */i < n);
        set(1, 0, n, i, val);
    }

    const T& set (u32 node, u32 l, u32 r, u32 i, T val) {
        if (i >= r || i < l)
            return a[node];
        if (l + 1 == r)
            return a[node] = val;
        u32 mid = (l + r) / 2;
        return a[node] = f(set(node * 2, l, mid, i, val), set(node * 2 + 1, mid, r, i, val));
    }
};

/* You can have range queries and updates, so long as you can calculate an update for a range
 * u_func(previous, length, lazy) -> new value
 * l_func(old_lazy, additional_lazy) -> new lazy value
 * The functions will be allowed to be passed as lambdas starting with C++20
 */
template<typename T, T q_neutral, T q_func(T,T), typename T_lazy, T_lazy u_neutral, T_lazy u_func(T, u32, T_lazy), T_lazy l_func(T_lazy, T_lazy)>
class UpdateSegmentTree {
private:
    vector<T> a;
    vector<T_lazy> lazy;
    u32 n;
public:
    /* Naming scheme for parameters:
     * node is 1-based index of current node, [l, r) is the range of the current node
     * [ql, qr) is range of the query, qi is index of a query
     */
    explicit UpdateSegmentTree(const vector<T>& init) : a(4 * init.size(), q_neutral), lazy(4 * init.size(), u_neutral), n(init.size()) {
        build(init, 1, 0, n);
    }

    explicit UpdateSegmentTree(u32 size) : a(4 * size, q_neutral), lazy(4 * size, u_neutral), n(size) { }

    const T& build(const vector<T>& init, u32 node, u32 l, u32 r) {
        if (l + 1 == r)
            return a[node] = init[l];
        u32 mid = (l + r) / 2;
        return a[node] = q_func(build(init, node * 2, l, mid),
                           build(init, node * 2 + 1, mid, r));
    }

    T operator[] (u32 i) {
        return query(i, i + 1);
    }

    T query(u32 ql, u32 qr) {
        assert(/* l >= 0 && */ql <= qr && qr <= n);
        return query(1, 0, n, ql, qr);
    }

    T query(u32 node, u32 l, u32 r, u32 ql, u32 qr) {
        if (ql >= r || qr <= l) // [l, r) and [ql, qr) are disjoint
            return q_neutral;
        lazily(node, l, r);
        if (ql <= l && r <= qr) // [l, r) is a subset of [ql, qr)
            return a[node];
        u32 mid = (l + r) / 2;
        return q_func(query(node * 2, l, mid, ql, qr), query(node * 2 + 1, mid, r, ql, qr));
    }

    void set(u32 qi, T val) {
        assert(/* i >= 0 && */qi < n);
        set(1, 0, n, qi, val);
    }

    const T& set (u32 node, u32 l, u32 r, u32 qi, T val) {
        lazily(node, l, r);
        if (qi >= r || qi < l)
            return a[node];
        if (l + 1 == r)
            return a[node] = val;
        u32 mid = (l + r) / 2;
        return a[node] = q_func(set(node * 2, l, mid, qi, val), set(node * 2 + 1, mid, r, qi, val));
    }

    void update (u32 ql, u32 qr, T val) {
        assert(/* l >= 0 && */ql <= qr && qr <= n);
        update(1, 0, n, ql, qr, val);
    }

    const T& update (u32 node, u32 l, u32 r, u32 ql, u32 qr, T val) {
        lazily(node, l, r);
        if (ql >= r || qr <= l) // [l, r) and [ql, qr) are disjoint
            return a[node];
        if (ql <= l && r <= qr) { // [l, r) is a subset of [ql, qr)
            lazy[node] = val;
            return lazily(node, l, r);
        }
        u32 mid = (l + r) / 2;
        return a[node] = q_func(update(node * 2, l, mid, ql, qr, val),
                           update(node * 2 + 1, mid, r, ql, qr, val));
    }

    const T& lazily (u32 node, u32 l, u32 r) {
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

    /* Assuming p: query([x, n)) × index -> bool is monotonic in x.
     * Returns the index of the first element x, such that query([x, n)) is true.
     * If no such element exists, returns n. ? actually n + 1 (see last sentence)
     * Complexity is O(log n) rather than O((log n)^2) by just binary searching from the outside
     * It might be possible to also expose the qr parameter, but I'm not sure yet.
     * Thank you bicsi, https://codeforces.com/blog/entry/83883
     * I don't understand this yet.
     * */
    template<typename Function>
    u32 search(u32 ql, const Function& p) {
        T acc_val = q_neutral;
        u32 acc_len = 0;
        return search(1, 0, n, ql, n, acc_val, acc_len, p);
    }

    template<typename Function>
    u32 search(u32 node, u32 l, u32 r, u32 ql, u32 qr, T& acc_val, u32& acc_len, const Function& p) {
        if (r <= ql)
            return n + 1; // sentinel value
        if (l >= qr)
            return l; // Why isn't this r?
        lazily(node, l, r);
        if (l >= ql && r <= qr && !p(acc_val + a[node], acc_len + r - l)) {
            acc_val = q_func(acc_val, a[node]);
            acc_len += r - l;
            return n + 1;
        }
        if (l + 1 == r)
            return l; // Why isn't this r?

        u32 mid = (l + r) / 2;
        u32 res = search(node * 2, l, mid, ql, qr, acc_val, acc_len, p);
        if (res != n + 1)
            return res;
        return search(node * 2 + 1, mid, r, ql, qr, acc_val, acc_len, p);
    }
};
// C++17:
i64 sum(i64 a, i64 b) { return a + b; }
i64 sum_lazy(i64 a, u32 len, i64 b) { return a + static_cast<i64>(len) * b; }
using sumST = UpdateSegmentTree<i64, 0, sum, i64, 0, sum_lazy, sum>;

// C++20:
// using sumST = UpdateSegmentTree<i64, 0, [](i64 a, i64 b) { return a + b; }, i64, 0, [](i64 a, u32 len, i64 b) { return a + static_cast<i64>(len) * b; }, [](i64 a, i64 b) { return a + b; }>;
