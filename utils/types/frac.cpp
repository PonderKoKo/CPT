#include "../macros.h"

struct frac {
	num p, q;
	constexpr frac(num a = 0, num b = 1) { num z = gcd(a, b) * (b > 0 ?: -1); p = a / z; q = b / z; }
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
