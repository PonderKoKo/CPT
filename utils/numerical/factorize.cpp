#include "is_prime.cpp"

multiset<num> factorize(num n) {
    if (n == 1) return {};
    if (is_prime(n)) return {n};
    num x = 0, y = 0, t = 30, z = 2, i = 1;
    auto f = [&] (__int128 x) { return x * x % n + i; };
    while (t++ % 40 || gcd(z, n) == 1) {
        if (x == y) y = f(x = ++i);
        z = __int128(z) * abs(x - y) % n ?: z;
        x = f(x), y = f(f(y));
    }
    auto a = factorize(z = gcd(z, n));
    return a.merge(factorize(n / z)), a;
}
