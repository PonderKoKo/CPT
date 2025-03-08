#include "../macros.h"

struct Compress : seq {
    Compress(vector<num*> a) {
        ranges::sort(a, {}, [] (num* x) { return *x; });
        for (auto x : a) {
            if (empty() || back() != *x)
                push_back(*x);
            *x = size() - 1;
        }
    }
};

// Usage: vector<num*> coords; for (all things to compress) coords.push_back(&thing); Compress decompress(coords);
// (all things have now been compressed) use decompress[thing] to get original values.
