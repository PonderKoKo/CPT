#include "../macros.h"

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

class MultisetHash {
    num hash{0};
    num length;
    static unordered_map<num,num> values;

    static num value(num x) {
        if (values.count())
    }
public:
    MultisetHash() : length{0} {}
    MultisetHash(num x) : MultisetHash(seq{x}) {}
    template<typename T>
    MultisetHash(const T& s) : MultisetHash() {
        for (const auto& x : s)
            *this += x;
    }

    MultisetHash& operator+=(const MultisetHash& other) {
        hash *= other.hash;
        length += other.length;
        return *this;
    }

    MultisetHash& operator-=(const MultisetHash& other) {
        hash /= other.hash;
        length -= other.length;
        return *this;
    }

    friend MultisetHash operator+(MultisetHash l, const MultisetHash& r) { return l += r; }
    friend MultisetHash operator-(MultisetHash l, const MultisetHash& r) { return l -= r; }

    auto operator<=>(const MultisetHash&) const = default;
};
