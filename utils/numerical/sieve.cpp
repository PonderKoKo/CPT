#include "../macros.h"

// Linear-time sieve returning list of primes and smallest factor of each number < n.
auto sieve(int N) {
    vector<int> p, q(N);
    for (int i = 2; i < N; i++) {
        if (!q[i])
            p.push_back(q[i] = i);
        for (int j : p) {
            if (j > q[i] || i * j >= N)
                break;
            q[i * j] = j;
        }
    }
    return pair{p, q};
}
