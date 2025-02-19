#include "../macros.h"

// Find [x, y, z] such that ax + by = z = gcd(a, b)
array<num,3> euclid(num a, num b) {
	if (!a) return {0, 1, b};
	auto [x, y, z] = euclid(b % a, a);
	return {y - b / a * x, x, z};
}

// Find x such that x = a (mod m) and x = b (mod n) or -1 if no such x exists
num crt(num a, num m, num b, num n) {
	auto [x, y, z] = euclid(m, n);
	if ((b -= a) % z)
		return -1;
	num l = m * n / z;
	return ((x * b / z % (n/z) * m + a) % l + l) % l;
}

// Find x such that ax = 1 mod (b) or -1 if no such x exists
num inv(num a, num b) {
	auto [x, y, z] = euclid(a, b);
	return z == 1 ? (x % b + b) % b : -1;
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
