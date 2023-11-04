#include "../macros.h"

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