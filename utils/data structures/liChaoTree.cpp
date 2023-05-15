#include "../macros.h"


using number = num;

// #define MINQ

// using number = double;
// #define DOUBLE

struct Line { // ax + b
    mutable number a, b, p;
    bool operator<(const Line& other) const { return a < other.a; }
    bool operator<(number x) const { return p < x; }
};

struct LiChaoTree : multiset<Line, less<>> {
    static const number infty = numeric_limits<number>::max();
#ifdef DOUBLE
    number div(number a, number b) { return a / b; }
#else
    number div(number a, number b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
#endif

    bool isect(iterator x, iterator y) {
        if (y == end())
            return x->p = infty, 0;
        if (x->a == y->a)
            x->p = x->b > y->b ? infty : -infty;
        else
            x->p = div(y->b - x->b, x->a - y->a);
        return x->p >= y->p;
    }
    void add(number a, number b) {
#ifdef MINQ
        a *= - 1, b *= -1;
#endif
        auto z = insert({a, b, 0}), y = z++, x = y;
        while (isect(y, z))
            z = erase(z);
        if (x != begin() && isect(--x, y))
            isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    number query(number x) const {
        assert(!empty());
        auto l = *lower_bound(x);
#ifdef MINQ
        return -l.a * x - l.b;
#else
        return l.a * x + l.b;
#endif
    }
};