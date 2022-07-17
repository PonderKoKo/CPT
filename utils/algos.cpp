#include "macros.h"

// Sadly Ranges is only available in C++20, using that with Algorithms library would be the cleanest.
/* Assuming the predicate p: [lo, hi) -> bool is monotonic (false then true),
 * returns the index of the first element in the range [lo, hi) that satisfies p.
 * If no such element is found, returns hi. This can be imagined as stipulating that p(hi) is true. */
template<typename num, typename Function>
num binary_weapon(num lo, num hi, const Function& p) {
    while (lo < hi) {
        num mid = (lo + hi) / 2;
        if (p(mid))
            hi = mid;
        else
            lo = mid + 1;
    }
    return lo;
}

bool binary_weapon_test_helper(i64 x) { return x >= 0; }

int main() {
    assert(binary_weapon(0, 10, [](int x) { return x > 5; }) == 6);
    assert(binary_weapon(0, 10, [](int x) { return x > 42; }) == 10);
    assert(binary_weapon(-1729, 2, binary_weapon_test_helper) == 0);
    vector<i64> v = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    assert(binary_weapon(0ul, v.size(), [&v](unsigned long x) {return v[x] > 0; }) == 2);
    return 0;
}