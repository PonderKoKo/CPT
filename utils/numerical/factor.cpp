#include "is_prime.cpp"

multiset<num> factor(num n) {
    if (n == 1) return {};
    if (is_prime(n)) return {n};
    auto f = [n] (__int128 x) { return ++(x *= x) %= n; };
    num x = 0, y = 0, t = 30, z = 2, i = 1;
    while (t++ % 40 || gcd(z, n) == 1) {
        if (x == y) y = f(x = ++i);
        z = z * abs(x - y) % n ?: z;
        x = f(x), y = f(f(y));
    }
    auto a = factor(z = gcd(z, n));
    return a.merge(factor(n / z)), a;
}
