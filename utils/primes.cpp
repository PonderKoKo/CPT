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

num modmul(num a, num b, num M) {
    return static_cast<num>(static_cast<__int128>(a) * b % M);
}
num modpow(num b, num e, num mod) {
    num ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1)
            ans = modmul(ans, b, mod);
    return ans;
}

bool isPrime(num n) {
    if (n < 2 || n % 6 % 4 != 1)
        return (n | 1) == 3;
    seq A{2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    num s = __builtin_ctzll(n - 1), d = n >> s;
    for (num a : A) {
        num p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = modmul(p, p, n);
        if (p != n-1 && i != s)
            return false;
    }
    return true;
}

num pollard(num n) {
    auto f = [n] (num x) { return modmul(x, x, n) + 1; };
    num x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while (t++ % 40 || gcd(prd, n) == 1) {
        if (x == y)
            x = ++i, y = f(x);
        if ((q = modmul(prd, max(x,y) - min(x,y), n)))
            prd = q;
        x = f(x), y = f(f(y));
    }
    return gcd(prd, n);
}
seq factor(num n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    num x = pollard(n);
    seq l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
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