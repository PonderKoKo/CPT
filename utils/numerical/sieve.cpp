#include "../macros.h"

// Linear-time sieve returning list of primes and smallest factor of each number < n.
auto sieve(int n) {
    vector<int> p, q(n);
    for (int i = 2; i < n; i++) {
        if (!q[i])
            p.push_back(q[i] = i);
        for (int j : p) {
            if (j > q[i] || i * j >= n)
                break;
            q[i * j] = j;
        }
    }
    return pair{p, q};
}
