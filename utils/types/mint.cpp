#pragma once
#include "../macros.h"

constexpr num m = ~42256ull/4;
struct mint {
    num a;
    mint(num x = 0) : a{x % m} { *this -= 0; }
#define op(n, T, a, b) \
    mint& operator n ## = (T o) { a; return *this b; } \
    friend mint operator n (mint x, T y) { return x n ## = y; }
    op(+, mint, a += o.a; if (a >= m) a -= m,)
    op(-, mint, a -= o.a; if (a < 0) a += m,)
    op(*, mint, a = __int128(a) * o.a % m,)
    op(/, mint, , *= !o)
    op(^, num, o %= m - 1; if (o < 0) o += m - 1; mint x = *this; for (*this = 1; o; o /= 2, x *= x) if (o & 1) *this *= x,)
    auto operator<=>(const mint& other) const = default;
    
    mint operator!() const { return *this ^ -1; }
    mint operator-() const { return -a; }
    friend istream& operator>>(istream& is, mint& x) { num z; return is >> z, x = z, is; }
    friend ostream& operator<<(ostream& os, mint x) { return os << x.a; }
    
    static mint b(int i) {
        static vector<mint> a{1, 1e9 + rng()}, c{1, 1 / a[1]};
        auto& z = i < 0 ? i = abs(i), c : a;
        while (size(z) <= i) z.push_back(z[1] * z.back());
        return z[i];
    }
    op(<<, num, , *= b(o))
    op(>>, num, , *= b(-o))
#undef op
};
