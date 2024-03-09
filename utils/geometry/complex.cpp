#include "../macros.h"

using d = double;
using c = complex<d>;

c dotcross(c a, c b) { return conj(a) * b; }
d dot(c a, c b) { return dotcross(a, b).real(); }
d cross(c a, c b) { return dotcross(a, b).imag(); }

c intersect(c a, c b, c p, c q) {
    d x = cross(p - a, b - a), y = cross(q - a, b - a);
    return (x * q - y * p) / (x - y);
}

int side(c s, c t, c p) {
    d x = cross(t - s, p - s);
    return (x > 0) - (x < 0);
}

bool onSegment(c s, c t, c p) {
    return !side(s, t, p) && dot(s - p, t - p) <= 0;
}