#include "../macros.h"

struct CmpSparseTable {
	using T = num;
#define cmp <=

	const vector<T> a;
	Graph m;

	CmpSparseTable(const vector<T>& v) : a(v), m(bit_width(size(a)), seq(size(a))) {
		iota(all(m[0]), 0ll);
		rep(l, ssize(m) - 1)
			for (num i = 0; i + (2 << l) <= ssize(a); i++)
				m[l+1][i] = a[m[l][i]] cmp a[m[l][i + (1 << l)]] ? m[l][i] : m[l][i + (1 << l)];
	}

	num argquery(num l, num r) const {
		auto t = bit_width(unsigned(r - l)) - 1;
		return a[m[t][l]] cmp a[m[t][r - (1 << t)]] ? m[t][l] : m[t][r - (1 << t)];
	}

	T query(num l, num r) const {
		return a[argquery(l, r)];
	}

#undef cmp
};

template<typename T>
struct OpSparseTable {
#define op(x, y) min(x, y)

	Table<T> m;

	OpSparseTable(const vector<T>& a) : m(bit_width(size(a)), vector<T>(size(a))) {
		m[0].assign(all(a));
		rep(l, ssize(m) - 1)
			for (num i = 0; i + (2 << l) <= ssize(a); i++)
				m[l+1][i] = op(m[l][i], m[l][i + (1 << l)]);
	}

	num query(num l, num r) const {
		auto t = bit_width(unsigned(r - l)) - 1;
		return op(m[t][l], m[t][r - (1 << t)]);
	}

#undef cmp
};

/* Benchmarking
 * mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	auto uid = uniform_int_distribution<num>(0, 6_e);
	vector<int> a(6_e);
	iota(all(a), 0);
	shuffle(all(a), rng);
	vector<par> queries(7_e);
	for (auto& [l, r] : queries) {
		while (l == r)
			l = uid(rng), r = uid(rng);
		if (l > r)
			swap(l, r);
	}
	auto begin = chrono::steady_clock::now();
	auto time = [&begin] (string desc) {
		cout << desc << ": " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - begin).count() << "ms" << endl;
		begin = chrono::steady_clock::now();
	};
	OpSparseTable st(a);
	time("Construction");
	for (const auto& [l, r] : queries)
		a[l] = st.query(l, r);
	time("Queries");
	return a[uid(rng)];
 */