#include "macros.h"

/* Sieve of Eratosthenes
 * Complexity: O(n log log n)
 * constructs bool array for numbers in [0, n)
 */
vector<bool> sieve(num n) {
    vector<bool> is_prime(n, true);
    is_prime[0] = is_prime[1] = false;
    for (num i = 2; i < n; ++i)
        if (is_prime[i])
            for (num j = i * i; j < n; j += i)
                is_prime[j] = false;
    return is_prime;
}

seq primes(num n) {
    auto is_prime = sieve(n);
    seq p;
    rep(i, n)
        if (is_prime[i])
            p.push_back(i);
    return p;
}

// Find x, y such that ax + by = gcd(a, b)
par euclid(num a, num b) {
    if (!a) return make_pair(0, 1);
    auto [x, y] = euclid(b % a, a);
    return make_pair(y - b / a * x, x);
}

// Find x such that x = a (mod m) and x = b (mod n)
num crt(num a, num m, num b, num n) {
    auto [x, y] = euclid(m, n);
    num g = gcd(m, n), d = b - a;
    if (d % g)
        return -1;
    num l = m / g * n;
    num r = (a + x * d / g % (l/m) * m) % l;
    return (r + l) % l;
}

num crt(const seq& a, const seq& m) {
    num x = 0, M = 1;
    rep(i, a.size()) {
        x = crt(x, M, a[i], m[i]);
        if (x == -1)
            return -1;
        M *= m[i] / gcd(m[i], M);
    }
    return x;
}

int main() {
    assert((sieve(10) == vector<bool>{false, false, true, true, false, true, false, true, false, false}));
    assert((factor(12) == seq{2, 2, 3}));
    assert((factor(1).empty()));
    return 0;
}