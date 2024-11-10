#pragma once
#include "../macros.h"

using d = double;
using c = complex<d>;
d dot(c a, c b) { return real(conj(a) * b); } // |a| * |b| * cos
d cross(c a, c b) { return imag(conj(a) * b); } // |a| * |b| * sin
bool lo(c a, c b = 0) { return (imag(a - b) ?: real(a - b)) < 0; }

// add explanations for norm, arg, abs ... https://mirror.codeforces.com/blog/entry/22175