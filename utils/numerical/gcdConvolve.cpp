#include "../macros.h"

// c[i] = sum over all j,k with gcd(j,k) = i of a[j] * b[k]
seq gcd_convolve(const seq& a, const seq& b) {
	seq c(min(size(a), size(b)));
	auto fft = [] (const seq& x, int i) {
		num z = 0;
		for (int j = i; j < ssize(x); j += i)
			z += x[j];
		return z;
	};
	for (int i = ssize(c) - 1; i >= 1; i--) {
		c[i] = fft(a, i) * fft(b, i);
		for (int j = 2 * i; j < ssize(c); j += i)
			c[i] -= c[j];
	}
	return c;
}