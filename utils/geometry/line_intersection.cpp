#include "complex.cpp"

// Returns intersection between lines st and pq.
// Real Part is NaN iff lines are parallel. Then imag is 1 iff lines are the same and 0 else.
c line_intersection(c s, c t, c p, c q) {
	d x = cross(p - s, t - s), y = cross(q - s, t - s);
	return x == y ? c(NAN, !x) : (x * q - y * p) / (x - y);
}