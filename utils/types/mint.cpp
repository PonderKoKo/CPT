#pragma once
#include "../macros.h"

template <num m = 4611686018427377339, int s = 0>
struct mint {
	num a;
	constexpr void ain() { if (a < 0) a += m; }
	constexpr mint(num x = 0) : a{x % m} { ain(); }
	#define op(n, T, a, b) \
	mint& operator n ## = (T o) { a; return *this b; }  \
	friend mint operator n (mint x, T y) { return x n ## = y; }
	op(+, mint, a += o.a - m; ain(),)
	op(-, mint, a -= o.a; ain(),)
	op(*, mint, a = (conditional_t<m<1<<30,num,__int128>) a * o.a % m,)
	op(/, mint, , *= !o)
	op(^, mint<m-1>, for (mint x{exchange(*this, 1)}; o.a; o.a /= 2, x *= x) if (o.a & 1) *this *= x,)
	op(<<, num, , *= b[o]; )
	op(>>, num, , *= b[s+1] * b[s-o]; )
	#undef op
	mint operator!() const { return *this ^ -1; }
	mint operator-() const { return -a; }
	friend istream& operator>>(istream& is, mint& x) { return is >> x.a, x.a %= m, x.ain(), is; }
	friend ostream& operator<<(ostream& os, mint x) { return os << x.a; }
	auto operator<=>(const mint& other) const = default;
	static mint *b;
};
template<num m, int s> mint<m, s> *mint<m, s>::b = [] {
	b = new mint<m,s>[s + 2];
	b[0] = 1;
	b[1] = uniform_int_distribution<num>(1e8, 2e8)(rng);
	rep(i, s - 1) b[i+2] = b[i + 1] * b[1];
	b[s + 1] = !b[s];
	return b;
}();
