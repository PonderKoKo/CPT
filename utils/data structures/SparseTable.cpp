#include "../macros.h"

template<typename T, typename cmp=less_equal<>>
struct CmpSparseTable {
	const vector<T> a;
	Table<int> m;

	CmpSparseTable(const vector<T>& v) : a(v), m(bit_width(size(a)), vector<int>(size(a))) {
		iota(all(m[0]), 0);
		rep(l, ssize(m) - 1)
			for (int i = 0; i + (2 << l) <= ssize(a); i++)
				m[l+1][i] = cmp{}(a[m[l][i]], a[m[l][i + (1 << l)]]) ? m[l][i] : m[l][i + (1 << l)];
	}

	num argquery(int l, int r) const {
		auto t = bit_width(unsigned(r - l)) - 1;
		return cmp{}(a[m[t][l]], a[m[t][r - (1 << t)]]) ? m[t][l] : m[t][r - (1 << t)];
	}

	T query(int l, int r) const {
		return a[argquery(l, r)];
	}
};

template<typename T, typename cmp = less<>> // less => max, greater => min
struct OpSparseTable {
    Table<T> m;

    OpSparseTable(const vector<T>& a) : m(bit_width(size(a)), vector<T>(size(a))) {
        if (!empty(a)) m[0].assign(all(a)); // !empty check specifically added for LCA which may construct an empty ST
        rep(l, ssize(m) - 1)
            for (num i = 0; i + (2 << l) <= ssize(a); i++)
                m[l+1][i] = max(m[l][i], m[l][i + (1 << l)], cmp{});
    }

    T query(int l, int r) const {
        auto t = bit_width(unsigned(r - l)) - 1;
        return max(m[t][l], m[t][r - (1 << t)], cmp{});
    }
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