#include "../macros.h"

using d = double;
using c = complex<d>;
c dotcross(c a, c b) { return conj(a) * b; }
d dot(c a, c b) { return dotcross(a, b).real(); }
d cross(c a, c b) { return dotcross(a, b).imag(); }


bool pcmp(c a, c b) { return pair{a.imag(), a.real()} < pair{b.imag(), b.real()}; }

c intersect(c a, c b, c p, c q) {
    d x = cross(p - a, b - a), y = cross(q - a, b - a);
    return (x * q - y * p) / (x - y);
}

/* Side of point p relative to line s-t */
int side(c s, c t, c p) {
    d x = cross(t - s, p - s);
    return (x > 0) - (x < 0);
}

bool onSegment(c s, c t, c p) {
    return !side(s, t, p) && dot(s - p, t - p) <= 0;
}

struct Angle {
    c x;
    int t;
    Angle(c x, int t = 0) : x(x), t(t) { assert(x != c(0)); }
    bool half() const { return pcmp(x, 0); }

};