#include "../macros.h"

auto sieve(num n) {
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
    auto view = views::iota(2ll, n) | views::filter([&] (num x) { return is_prime[x]; });
    return {all(view)};
}