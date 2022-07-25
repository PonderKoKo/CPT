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

template<typename T, T neutral, T f(T,T)>
class UpdateSegmentTree {
private:
    vector<T> a;
    vector<T> lazy; /* for + only */
    u32 n;
public:
    explicit UpdateSegmentTree(const vector<T>& init) : a(4 * init.size(), neutral /* necessary? */), n(init.size()), lazy(4 * init.size(), neutral) {
        build(init, 1, 0, n);
    }

    explicit UpdateSegmentTree(u32 size) : a(4 * size, neutral /* necessary? */), lazy(4 * size, neutral), n(size) {
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

    T operator[] (u32 i) {
        return query(i, i + 1);
    }

    T query(u32 l, u32 r) {
        assert(/* l >= 0 && */l <= r && r <= n);
        return query(1, 0, n, l, r);
    }

    T query(u32 node, u32 l, u32 r, u32 ql, u32 qr) {
        if (ql >= r || qr <= l) // [l, r) and [ql, qr) are disjoint
            return neutral;
        lazily(node, l, r);
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
        lazily(node, l, r);
        if (i >= r || i < l)
            return a[node];
        if (l + 1 == r)
            return a[node] = val;
        u32 mid = (l + r) / 2;
        return a[node] = f(set(node * 2, l, mid, i, val), set(node * 2 + 1, mid, r, i, val));
    }

    void update (u32 l, u32 r, T val) {
        assert(/* l >= 0 && */l <= r && r <= n);
        update(1, 0, n, l, r, val);
    }

    const T& update (u32 node, u32 l, u32 r, u32 ql, u32 qr, T val) {
        lazily(node, l, r);
        if (ql >= r || qr <= l) // [l, r) and [ql, qr) are disjoint
            return a[node];
        if (ql <= l && r <= qr) { // [l, r) is a subset of [ql, qr)
            lazy[node] += val;
            return lazily(node, l, r);
        }
        u32 mid = (l + r) / 2;
        return a[node] = f(update(node * 2, l, mid, ql, qr, val),
                           update(node * 2 + 1, mid, r, ql, qr, val));
    }

    const T& lazily (u32 node, u32 l, u32 r) {
        if (lazy[node] == neutral)
            return a[node];
        a[node] += static_cast<i32>(r - l) * lazy[node];
        if (l + 1 < r) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = neutral;
        return a[node];
    }
};
