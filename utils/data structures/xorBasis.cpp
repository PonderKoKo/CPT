#include "../macros.h"

struct XORBasis {
    using U = unsigned;
    static constexpr U m{31};
    array<U,m> basis{};
    XORBasis() = default;
    XORBasis& operator+= (U x) {
        while (x) {
            U& b = basis[bit_width(x) - 1];
            if (!b)
                b = x;
            x ^= b;
        }
        return *this;
    }

    bool operator[](U x) const {
        while (x) {
            const U& b = basis[bit_width(x) - 1];
            if (!b)
                return false;
            x ^= b;
        }
        return true;
    }

    XORBasis& operator+= (const XORBasis& other) {
        for (const auto& x : other.basis)
            *this += x;
        return *this;
    }

    num size() const {
        return m - count(all(basis), 0);
    }

    U max(U mask = 0) const {
        U v{0ull};
        for (U i = m - 1; ~i; i--)
            if ((v ^ basis[i] ^ mask) & 1ull << i)
                v ^= basis[i];
        return v ^ mask;
    }
    U min(U mask = 0) const { return max(~mask) ^ ~mask; }
    friend XORBasis operator+ (XORBasis self, U x) { return self += x; }
    friend XORBasis operator+ (XORBasis self, XORBasis other) { return self += other; }
};