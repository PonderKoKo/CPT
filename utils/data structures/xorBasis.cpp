#include "../macros.h"

template<int m>
struct XORBasis {
	array<ull,m> b{};
	#define y b[bit_width(x) - 1]
	void update(ull x) { while (x) x ^= y ?: y = x; }
	bool query(ull x) { return !x || y && query(x ^ y); }
	#undef y
	int size() { return m - count(all(b), 0); }
    ull min(ull v = 0) {
		for (int i = m; i--;)
			if (v >> i & 1)
				v ^= b[i];
		return v;
	}
    ull max(ull v = 0) { return ~min(~v); }
};
