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
#undef op
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

    int search(int v, int l, int r, auto& p) {
        push(v, l, r);
        return ql >= r ? 0 : ql <= l && p(qf(qy, q[v]), r) ? qy = qf(qy, q[v]), 0 : l + 1 == r ? r :
        search(v + 1, l, (l + r) / 2, p) ?: search(v + (r - l & ~1), (l + r) / 2, r, p);
    }

public:
    SegTreeL(int n) : n(n), q(2 * n - 1, qn), u(2 * n - 1, un) {}
    SegTreeL(const vector<Q> &a) : SegTreeL(size(a)) { build(a, 0, 0, n); }
    Q query(int l, int r) { return ql = l, qr = r, _query(0, 0, n); }
    void update(int l, int r, U x) { ql = l, qr = r, qx = x, _update(0, 0, n); }
    void set(int i, Q y) { ql = i, qr = i + 1, qy = y, _set(0, 0, n); }
    // Returns minimum r > l, s. t. p(query(l, r), r) is false or 0 if always true.
    int search(int l, auto p) { return ql = l, qy = qn, search(0, 0, n, p); }
};
using MaxAddST = SegTreeL<num,num,numeric_limits<num>::min(),0,ranges::max,[](num x, num y, int l, int r) { return x + y; },plus<>{}>;