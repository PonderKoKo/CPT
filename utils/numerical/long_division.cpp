#include "../macros.h"

// Complexity is |p| * |q|, higher order terms placed at the higher indices.
// Return value is remainder concatenated with quotient, first |q| - 1 values are remainder, remaining |p| - (|q| - 1) are quotient
// The optimization with inverse is good for modulo, but presumably bad for everything else.
template<typename T>
vector<T> long_division(vector<T> p, const vector<T>& q) {
    T inv = 1 / q.back();
    for (int i = size(p); i-- >= size(q);) {
        p[i] *= inv;
        rep(j, size(q) - 1)
            p[i - size(q) + j + 1] -= q[j] * p[i];
    }
    return p;
}
