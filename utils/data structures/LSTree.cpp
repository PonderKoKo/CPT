#include "../types/mint.cpp"

struct LSTree {
    using Q = mint; // !!
    using U = pair<mint,mint>; // !!
    LSTree(int n) : q(2 * n, 0), u(2 * n, {1, 0}) {} // !!x2
    static Q qf(Q a, Q b) { return a + b; } // !!
    void push(int v, int l, int r) {
        q[v] = q[v] * u[v].first + (r - l) * u[v].second; // !!
        if (l + 1 < r) for (int c : {1, r - l & ~1}) {
            u[v + c] = {u[v + c].first * u[v].first, u[v + c].second * u[v].first + u[v].second}; // !!
        }
        u[v] = u[0];
    }

    vector<Q> q;
    vector<U> u;
#define op(f, qr, a, b, c, d...)\
	Q f(int ql, d, int l = 0, int r = 0, int v = 1) {\
		push(v, l, r = r ?: size(q) / 2);\
		return qr <= l || r <= ql ? a\
			 : ql <= l && r <= qr ? b : c\
		qf( f(ql, d, l, (l+r) / 2, v + 1),\
			f(ql, d, (l+r) / 2, r, v + (r-l & ~1)) ); }
    op(query, qr, q[0], q[v], , int(qr))
    op(update, qr, q[v], (u[v] = x, push(v, l, r), q[v]), q[v] =, int(qr), U(x))
    op(set, ql + 1, q[v], q[v] = x, q[v] =, Q(x))
    op(build, l + 1, , q[v] = ((Q*)a)[l], q[v] =, num(a))
#undef op
    LSTree(const vector<Q> &a) : LSTree(size(a)) { build(0, num(&a[0])); }
};
