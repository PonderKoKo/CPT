#include "../macros.h"

template<typename T, auto f = ranges::min>
struct SparseTable {
	Table<T> m;
	SparseTable(const vector<T>& a) : m{a} {
		for (int l = 2; l <= size(a); l *= 2) {
			m.emplace_back(size(a) - l + 1);
			rep(i, size(m.back()))
				m.back()[i] = f(end(m)[-2][i], end(m)[-2][i + l / 2]);
		}
    }

    T query(int l, int r) const {
        int t = bit_width(u_int(r - l)) - 1;
        return f(m[t][l], m[t][r - (1 << t)]);
    }
};
