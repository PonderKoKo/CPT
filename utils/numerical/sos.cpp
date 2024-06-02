#include "../macros.h"

/* Sum over Subsets DP
 * Given array a of 2^n integers, computes b[i] := sum_{j|j&i=j} a[i].
 * Complexity: O(n * 2^n)
 * Same technique can be used for other aggregates.
 * Can be used to sum over supersets by taking the inverse of everything.
 * About 2x faster than implementation in kactl / https://codeforces.com/blog/entry/45223.
 */
seq sos(seq a) {
    assert(has_single_bit(size(a)));
    for (uint i = 1; i < size(a); i *= 2)
        for (uint j = i; j < size(a); j += i)
            for (; j & i; j++)
                a[j] += a[i ^ j];
    return a;
}