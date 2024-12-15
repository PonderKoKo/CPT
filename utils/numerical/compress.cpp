#include "../macros.h"

seq compress(vector<num*> a) {
    seq b;
    ranges::sort(a, {}, [] (num* x) { return *x; });
    for (auto x : a) {
        if (empty(b) || b.back() != *x)
            b.push_back(*x);
        *x = size(b) - 1;
    }
    return b;
}
// Usage: vector<num*> coords; for (all things to compress) coords.push_back(&thing); seq decompress = compress(coords);
// (all things have now been compressed) use decompress[thing] to get original values.
