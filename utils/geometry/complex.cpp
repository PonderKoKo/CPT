#pragma once
#include "../macros.h"

using d = num;
using c = complex<d>;
d dot(c a, c b) { return real(conj(a) * b); } // |a| * |b| * cos
d cross(c a, c b) { return imag(conj(a) * b); } // |a| * |b| * sin
bool lo(c a, c b = 0) { return (imag(a -= b) ?: real(a)) < 0; }
namespace std {
    auto operator<=>(c a, c b) { return (real(a -= b) ?: imag(a)) <=> 0; }
    istream& operator>>(istream& is, c& a) { d x; return is >> x, a.real(x), is >> x, a.imag(x), is; }
    ostream& operator<<(ostream& os, c& a) { return os, real(a), imag(a); }
}
// norm is x^2 + y^2. abs is sqrt(norm). arg is atan2(y, x) (angle to x-axis in [-pi, pi]).