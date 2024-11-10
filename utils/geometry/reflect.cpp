#include "complex.cpp"

// floating-point only!
// Reflects p across line st (returning x)
//    p
// s----t
//    x
c reflect(c p, c s, c t) {
	return s + conj((p - s) / (t - s)) * (t - s);
}
