#include "../macros.h"

bool is_prime(num n) {
    if (n < 2 || n % 6 % 4 != 1)
        return n / 2 == 1;
    num s = countr_zero(n - 1ull);
    return ranges::all_of(seq{2, 325, 9375, 28178, 450775, 9780504, 1795265022}, [&] (num a) {
        __int128 p = 1, b = a, i = s;
        for (num d = n >> s; d; (b *= b) %= n, d /= 2)
            if (d & 1)
                (p *= b) %= n;
        while (p != 1 && p != n - 1 && a % n && i--)
            (p *= p) %= n;
        return p == n - 1 || i == s;
    });
}
