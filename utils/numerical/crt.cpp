#include "../macros.h"

// Find x, y such that ax + by = gcd(a, b)
par euclid(num a, num b) {
	if (!a) return {0, 1};
	auto [x, y] = euclid(b % a, a);
	return par(y - b / a * x, x);
}

// Find x such that x = a (mod m) and x = b (mod n)
num crt(num a, num m, num b, num n) {
	auto [x, y] = euclid(m, n);
	num g = gcd(m, n), d = b - a;
	if (d % g)
		return -1;
	num l = m / g * n;
	num r = (a + x * d / g % (l/m) * m) % l;
	return (r + l) % l;
}

num crt(const seq& a, const seq& m) {
	num x = 0, M = 1;
	rep(i, a.size()) {
		x = crt(x, M, a[i], m[i]);
		if (x == -1)
			return -1;
		M *= m[i] / gcd(m[i], M);
	}
	return x;
}