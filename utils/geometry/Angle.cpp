#include "complex.cpp"

struct Angle {
	c x; int t = 0;
	auto operator<=>(const Angle& a) const {
		return tuple{t, lo(x), imag(x) * real(a.x)}
		<=> tuple{a.t, lo(a.x), real(x) * imag(a.x)};
	}
};