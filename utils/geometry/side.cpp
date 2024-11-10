#include "complex.cpp"

// integer!
// Returns sign for side of p relative to line st.
//   +1
// s--0--t
//   -1
int side(c p, c s, c t) {
	d x = cross(t - s, p - s);
	return (x > 0) - (x < 0);
}
