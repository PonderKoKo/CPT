#include "../macros.h"

template<auto c = less{}, double eps = 1e-8> // Change to greater{} for maximum
double gss(double a, double b, auto &&f) {
    for (double p = numbers::phi, x = (b - a) / p, f1 = f(b - x), f2 = f(a + x); b - a > eps; swap(f1, f2))
        if (c(f1, f2))
            b = a + x, f2 = f(b - (x /= p));
        else
            a = b - x, f1 = f(a + (x /= p));
    return a;
}