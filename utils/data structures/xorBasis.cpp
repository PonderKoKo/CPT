#include "../macros.h"

template<int m>
struct XORBasis {
	using U = conditional<32 < m,ull,unsigned>::type;
	array<U,m> b{};
	#define y b[bit_width(x) - 1]
	void update(U x) { while (x) x ^= y ?: y = x; }
	bool query(U x) { return !x || y && query(x ^ y); }
	#undef y
	int size() const { return m - count(all(b), 0); }
	U min(U v = 0) const {
		for (int i = m; i--;)
			if (v >> i & 1)
				v ^= b[i];
		return v;
	}
	U max(U v = 0) const { return ~min(~v); }
};
