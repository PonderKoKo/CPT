#include "macros.h"

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

int main() {
    return 0;
}