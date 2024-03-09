#include "../macros.h"

template <typename Q, typename U, auto qn, U un, auto qf, auto uf, auto pf>
class SegTreeL {
    vector<Q> q;
    vector<U> u;
    int n, ql, qr;
    U qx;
    Q qy;
#define op(n, a, b, c) Q n(int v, int l, int r) { push(v, l, r); return ql >= r || qr <= l ? a : ql <= l && r <= qr ? b\
: c qf(n(v + 1, l, (l + r) / 2), n(v + (r - l & ~1), (l + r) / 2, r)); }
    op(_query, qn, q[v],)
    op(_update, q[v], (u[v] = qx, push(v, l, r), q[v]), q[v] =)
    op(_set, q[v], q[v] = qy, q[v] =)

    void push(int v, int l, int r) {
        q[v] = uf(q[v], u[v], l, r);
        if (l + 1 < r)
            for (int c : {v + 1, v + (r - l & ~1)})
                u[c] = pf(u[c], u[v]);
        u[v] = un;
    }

    Q build(const vector<Q> &a, int v, int l, int r) {
        return q[v] = l + 1 == r ? a[l] : qf(build(a, v + 1, l, (l + r) / 2), build(a, v + (r - l & ~1), (l + r) / 2, r));
    }
public:
    SegTreeL(int n) : n(n), q(2 * n - 1, qn), u(2 * n - 1, un) {}
    SegTreeL(const vector<Q> &a) : SegTreeL(size(a)) { build(a, 0, 0, n); }
    Q query(int l, int r) { return ql = l, qr = r, _query(0, 0, n); }
    void update(int l, int r, U x) { ql = l, qr = r, qx = x, _update(0, 0, n); }
    void set(int i, Q y) { ql = i, qr = i + 1, qy = y, _set(0, 0, n); }
};
using SumAddST = SegTreeL<num,num,0,0,plus<>{},[](num x, num y, int l, int r) { return x + y * (r - l); },plus<>{}>;


/* Assuming p: query([ql, x)) × interval_length -> bool is monotonic in x.
   * Returns the index of the first element x, such that query([ql, x)) is true.
   * If no such element exists, returns n + 1
   * Complexity is O(log n) rather than O((log n)^2) by just binary searching
   * from the outside
   */
/*
num search(num ql, const function<bool(T, num)> &p) {
    T acc_val = q_neutral;
    num acc_len = 0;
    return search(1, 0, n, ql, n, acc_val, acc_len, p);
}

num search(num node, num l, num r, num ql, num qr, T &acc_val, num &acc_len,
           const function<bool(T, num)> &p) {
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
}*/