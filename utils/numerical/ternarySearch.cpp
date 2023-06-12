#include "../macros.h"

// Finds maximum
num ternarySearch(num lo, num hi, const function<num(num)> f) {
    while (lo + 1 < hi) {
        num mid = (lo + hi) / 2;
        (f(mid) > f(mid + 1) ? hi : lo) = mid;
    }
    return lo + 1; // Isn't this just hi?
}