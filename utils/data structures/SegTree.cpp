#include "../macros.h"

struct SegTree {
	using T = num;
	static constexpr T unit = numeric_limits<num>::max();
	static T f(T a, T b) {
		return min(a, b);
	}
	int n;
	vector<T> s;

	explicit SegTree(int size) : n(size), s(2*n, unit) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int l, int r) const {
		T ra = unit, rb = unit;
		for (l += n, r += n; l < r; l /= 2, r /= 2) {
			if (l % 2) ra = f(ra, s[l++]);
			if (r % 2) rb = f(s[--r], rb);
		}
		return f(ra, rb);
	}
	// All Following is Optional
	explicit SegTree(const vector<T>& a) : n(size(a)), s(2*n, unit) {
		rep(i, n)
			s[i + n] = a[i];
		for (num i = n - 1; i > 0; --i)
			s[i] = f(s[i * 2], s[i * 2 + 1]);
	}
	T operator[](int i) const { // TODO Untested
		return s[n + i];
	}

	// Assuming p monotonic: Returns last r such that p(query(l, r)) is false (n if always)
	int search(int l, const function<bool(T)>& p) const {
		vector<int> a, b;
		int r = n;
		for (l += n, r += n; l < r; l /= 2, r /= 2) {
			if (l % 2) a.push_back(l++);
			if (r % 2) b.push_back(--r);
		}
		a.insert(a.end(), b.rbegin(), b.rend());
		T acc = unit;
		for (int i : a) {
			if (p(f(acc, s[i]))) {
				while (i < n) {
					i *= 2;
					if (!p(f(acc, s[i])))
						acc = f(acc, s[i++]);
				}
				return i - n;
			}
			acc = f(acc, s[i]);
		}
		return n;
	}
};