#include "../macros.h"

#include "../types/modular.cpp"

using mod = modular<4'611'686'018'427'387'847>;
class RollingHash {
    static const mod base;
    num length{0};
    mod hash{0};

public:
    RollingHash() = default;
    RollingHash(num l, mod h) : length{l}, hash{h} {}
    RollingHash(const auto& s) :
            length{ssize(s)},
            hash{accumulate(rbegin(s), rend(s), mod(0), [](mod acc, const auto& x) { return acc * base + x; })}
    {}
    RollingHash(num i, num x) :
            length{i + 1},
            hash{x * (base ^ i)}
    {}
    explicit operator mod() { return hash; }

    RollingHash operator+(const RollingHash& other) const {
        return RollingHash{max(length, other.length), hash + other.hash};
    }

    RollingHash operator-() const {
        return RollingHash{length, -hash};
    }

    RollingHash operator-(const RollingHash& other) const {
        return *this + -other;
    }

    RollingHash operator>>(const num& x) const {
        return RollingHash{length + x, hash * (base ^ x)};
    }

    RollingHash operator<<(const num& x) const {
        return *this >> -x;
    }

    // Concatenation
    RollingHash operator*(const RollingHash& other) {
        return *this + (other >> length);
    }

    // Prefix Deletion
    RollingHash operator/(const RollingHash& other) const {
        return (*this - other) << other.length;
    }

    struct hashify { num operator() (RollingHash r) const { return num(r.hash); } };

    RollingHash& operator+=(const RollingHash& other) { return *this = *this + other; }
    RollingHash& operator-=(const RollingHash& other) { return *this = *this - other; }
    RollingHash& operator>>=(const num& x) { return *this = *this >> x; }
    RollingHash& operator<<=(const num& x) { return *this = *this << x; }
    RollingHash& operator*=(const RollingHash& other) { return *this = *this * other; }
    RollingHash& operator/=(const RollingHash& other) { return *this = *this / other; }
    auto operator<=>(const RollingHash&) const = default;
};
const mod RollingHash::base{uniform_int_distribution<num>(1e3, 1e9)(rng)};