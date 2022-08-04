#include "macros.h"

/* Sieve of Eratosthenes
 * Complexity: O(n log log n)
 * constructs bool array for numbers in [0, n)
 */
vector<bool> sieve(u32 n) {
    vector<bool> is_prime(n, true);
    is_prime[0] = is_prime[1] = false;
    for (u32 i = 2; i < n; ++i)
        if (is_prime[i])
            for (u32 j = i * i; j < n; j += i)
                is_prime[j] = false;
    return is_prime;
}

/* Naive Trial Division
 * Complexity: O(sqrt(n))
 * returns list of prime factors of n
 */
vector<u32> factorize(u32 n) {
    vector<u32> factors;
    for (u32 i = 2; i * i <= n; ++i)
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    if (n > 1)
        factors.push_back(n);
    return factors;
}

int main() {
    assert((sieve(10) == vector<bool>{false, false, true, true, false, true, false, true, false, false}));
    assert((factorize(12) == vector<u32>{2, 2, 3}));
    assert((factorize(1).empty()));
    return 0;
}