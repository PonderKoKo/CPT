#include "complex.cpp"

// Returns intersection between lines st and pq.
// Real Part is NaN iff lines are parallel. Then imag is 1 iff lines are the same and 0 else.
c line_intersection(c s, c t, c p, c q) {
    d x = cross(p - s, t - s), y = cross(q - s, t - s);
    return x == y ? c(NAN, !x) : (x * q - y * p) / (x - y);
}

// Projects p onto line st (returning x)
// s--x-t
//    p
c project(c p, c s, c t) {
    return s + (t - s) * dot(p - s, t - s) / norm(t - s);
}

// Reflects p across line st (returning x)
//    p
// s----t
//    x
c reflect(c p, c s, c t) {
    return s + conj((p - s) / (t - s)) * (t - s);
}

// From a via b to c. [-pi, pi]
double angle_ccw(c a, c b, c c) {
    return arg((c - b) / (a - b));
}
// Takes a value in [-pi, pi] (like from arg or angle_ccw) and returns it mod 2pi, i.e. in [0, 2pi)
double angle_p(double x) {
    return x < 0 ? x + 2 * numbers::pi : x;
}
constexpr double DEG_RAD = 180 / numbers::pi; // * DEG_RAD for radians to degrees, / for degrees to radians.
