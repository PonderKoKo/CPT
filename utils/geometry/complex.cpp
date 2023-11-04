#include "../macros.h"

// Cross Product
template<typename T> T operator%(const complex<T>& a, const complex<T>& b) { return (conj(a) * b).imag(); }
template<typename T> bool turnsCCW(const complex<T>& a, const complex<T>& b) { return a % b > 0; }


// UNFINISHED
template<typename T>
complex<T> lineIntersection(complex<T> a, complex<T> b, complex<T> p, complex<T> q) {
	auto c = (p - a) % (b - a), d = (q - a) % (b - a);
	return c - d ? (c * q - d * p) / (c - d) : numeric_limits<complex<T>>::max() * (!c ?: -1);
}