#pragma once
#include "../macros.h"

constexpr num mod = 998244353; // ~42256ull/4; // for hashing
struct mint {
    conditional_t<mod<1<<31,int,num> a;
    mint(num x = 0) : a(x % mod) { if (a < 0) a += mod; }
#define op(n, T, a, b) \
mint& operator n ## = (T o) { a; return *this b; } \
friend mint operator n (mint x, T y) { return x n ## = y; }
    op(+, mint, a += o.a; if (a >= mod) a -= mod,)
    op(-, mint, a -= o.a; if (a < 0) a += mod,)
    op(*, mint, a = (conditional_t<mod<1<<31,num,__int128>) a * o.a % mod,)
    op(/, mint, , *= !o)
    op(^, num, o %= mod - 1; if (o < 0) o += mod - 1; mint x = *this; for (*this = 1; o; o /= 2, x *= x) if (o & 1) *this *= x,)
    auto operator<=>(const mint& other) const = default;
    mint operator!() const { return *this ^ -1; }
    mint operator-() const { return -a; }
    friend istream& operator>>(istream& is, mint& x) { num z; return is >> z, x = z, is; }
    friend ostream& operator<<(ostream& os, mint x) { return os << x.a; }
    static mint b(int i) {
        static vector<mint> a{1, 1e9 + rng()}, c{1, !a[1]};
        auto& z = i < 0 ? i = -i, c : a;
        while (size(z) <= i) z.push_back(z[1] * z.back());
        return z[i];
    }
    op(<<, num, , *= b(o))
    op(>>, num, , *= b(-o))
#undef op
};
