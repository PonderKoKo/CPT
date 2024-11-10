#include "../macros.h"
#include <limits>

struct LSTree {
	using Q = num; // !!
	using U = num; // !!
	LSTree(int n) : q(2 * n, numeric_limits<num>::min()), u(2 * n, 0) {} // !!x2
	static Q qf(Q a, Q b) { return max(a, b); } // !!
	void push(int v, int l, int r) {
		q[v] += u[v]; // !!
		if (l + 1 < r)
			for (int c : {v + 1, v + (r - l & ~1)})
				u[c] += u[v]; // !!
		u[v] = u[0];
	}
	
	vector<Q> q;
	vector<U> u;
#define op(f, qr, a, b, c, d...)								\
	Q f(int ql, d, int v = 1, int l = 0, int r = 0) {			\
		push(v, l, r = r ?: size(q)/2);							\
		return ql >= r || qr <= l  ? a							\
			 : ql <= l && r  <= qr ? b : c						\
		qf( f(ql, d, v + 1, 		 l, (l+r) / 2),				\
			f(ql, d, v + (r-l & ~1), (l+r) / 2, r) ); }
	op(query, qr, q[0], q[v], , int(qr))
	op(update, qr, q[v], (u[v] = x, push(v, l, r), q[v]), q[v] =, int(qr), U(x))
	op(set, ql + 1, q[v], q[v] = x, q[v] =, Q(x))
#undef op
	
	Q build(const vector<Q> &a, int v, int l, int r) {
		return q[v] = l + 1 == r ? a[l] : qf(build(a, v + 1, l, (l+r) / 2), build(a, v + (r-l & ~1), (l+r) / 2, r));
	}
	LSTree(const vector<Q> &a) : LSTree(size(a)) { build(a, 1, 0, size(a)); }
	int search(int ql, auto&& p) {
		Q x{q[0]};
		for (stack<array<int,3>> w{{{1, 0, (int) size(q) / 2}}};; w.pop()) {
			auto [v, l, r] = w.top();
			if (ql >= r || ql <= l && p(qf(x, q[v]), r) && (x = qf(x, q[v]), true))
				continue;
			if (l + 1 == r) return r;
			w.emplace(v + (r-l & ~1), (l+r) / 2, r);
			w.emplace(v + 1, l, (l+r) / 2);
		}
		return -1;
	}
};