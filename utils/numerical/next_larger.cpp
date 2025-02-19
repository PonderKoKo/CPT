#include "../macros.h"

/* Next Larger Element
 * Complexity: O(n)
 * Returns for each index i the (nx ? smallest j > i [or n] : biggest j < i [or -1]), such that c(a[i], a[j]).
 * Works for c in {less, greater, less_equal, greater_equal, not_equal_to}.
 */
seq next_larger(const seq& a, auto c = less<>{}, bool nx = true) {
    int n = size(a);
    seq b(n, nx ?: -1);
    rep(k, n) {
        num i = nx ? n - k - 1 : k, &x = b[i] += i;
        while (0 <= x && x < n && !c(a[i], a[x]))
            x = b[x];
    }
    return b;
}
