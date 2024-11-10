#include "../macros.h"

template<typename T = num>
struct frac {
	T p, q;
	constexpr frac(T a = 0, T b = 1) { T z = gcd(a, b) * (b > 0 ?: -1); p = a / z; q = b / z; }
	#define op(n, a...) \
	frac& operator n ## = (const frac& o) { return *this = *this n o; }  \
	frac operator n (const frac& o) const { return a; }
	op(+, {p * o.q + q * o.p, q * o.q})
	op(-, *this + -o)
	op(*, {p * o.p, q * o.q})
	op(/, *this * !o)
	
	frac operator-() const { return {-p, q}; }
	frac operator!() const { return {q, p}; }
	auto operator<=>(const frac& o) const { return p * o.q <=> q * o.p; }
	bool operator==(const frac& o) const = default;
};
