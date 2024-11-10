#include "complex.cpp"

// floating-point only!
// Projects p onto line st (returning x)
// s--x-t
//    p
c project(c p, c s, c t) {
	return s + (t - s) * dot(p - s, t - s) / norm(t - s);
}
