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

u32 count_bits(u64 n) {
    u32 count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

/* Counts inversions using Merge Sort.
 * Complexity: O(n log n)
 * l inclusive, r exclusive
 */
template<typename T>
u64 count_inversions(vector<T>& a, vector<T>& temp, u32 l, u32 r) {
    u64 count = 0;
    if (r - l == 1)
        return 0;
    u32 mid = (l + r) / 2;
    count += count_inversions(a, temp, l, mid);
    count += count_inversions(a, temp, mid, r);

    u32 i, j, k;
    for (i = l, j = mid, k = l; i < mid && j < r; ++k) {
        if (a[i] <= a[j])
            temp[k] = a[i++];
        else {
            temp[k] = a[j++];
            count += mid - i;
        }
    }

    while (i < mid)
        temp[k++] = a[i++];
    while (j < r)
        temp[k++] = a[j++];
    for (i = l; i < r; ++i)
        a[i] = temp[i];

    return count;
}

template<typename T>
u64 count_inversions(vector<T> a) {
    vector<T> temp(a.size());
    return count_inversions(a, temp, 0, a.size());
}

vector<u64> variable_base_encoding(vector<u64>& bases, u64 x) {
    vector<u64> result(bases.size(), 0);
    vector<u64> values(bases.size(), 0);
    u64 value = 1;
    i32 i;
    for (i = 0; value <= x; ++i) {
        assert(i < bases.size()); // Otherwise x isn't representable
        values[i] = value;
        value *= bases[i];
    }
    for (--i; i >= 0; --i) {
        result[i] = x / values[i];
        x %= values[i];
    }
    return result;
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