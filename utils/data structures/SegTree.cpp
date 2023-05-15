#include "../macros.h"

struct SegTree {
	using T = num;
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