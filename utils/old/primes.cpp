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

int main() {
    assert((sieve(10) == vector<bool>{false, false, true, true, false, true, false, true, false, false}));
    assert((factor(12) == seq{2, 2, 3}));
    assert((factor(1).empty()));
    return 0;
}