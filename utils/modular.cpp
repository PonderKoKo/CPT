#include "macros.h"

template <i64 Modulo>
class modular {
    static_assert(Modulo > 0, "Modulo must be positive");
private:
    static vector<modular> factorials;
    i64 _a;
    const i64 _m = Modulo;

    void normalize () {
        if (_a >= _m || -_a <= _m)
            _a %= _m;
        if (_a < 0)
            _a += _m;
    }

public:
    modular (const modular& m = modular(0)) : _a(m._a) { }

    modular (const i64& a)
            : _a (a)
    { normalize(); }

    explicit operator i64() { return _a; };

    modular& operator = (const modular& m) {
        _a = m._a;
        return *this;
    }

    modular& operator += (const modular& other) {
        _a += other._a;
        if (_a >= _m)
            _a -= _m;
        return *this;
    }

    modular& operator -= (const modular& other) {
        _a -= other._a;
        if (_a < 0)
            _a += _m;
        return *this;
    }

    modular& operator *= (const modular& other)
    { return _a *= other._a, normalize(), *this; }

    modular& operator /= (const modular& other)
    { return *this *= !other; }

    // Binary Exponentiation, untested
    modular& operator ^= (u64 power) {
        auto base = *this;
        *this = 1;
        while (power > 0) {
            if (power & 1)
                *this *= base;
            base *= base;
            power >>= 1;
        }
        return *this;
    }

    modular& operator ++ () { return *this += 1; }
    modular& operator -- () { return *this -= 1; }
    const modular operator ++ (int) { const modular result (*this); ++*this; return result; }
    const modular operator -- (int) { const modular result (*this); --*this; return result; }

    modular operator + () const { return *this; }
    modular operator - () const { return modular(-_a); }
    // Fermat Inverse, assuming m is prime
    modular operator ! () const {
        return *this ^ (_m - 2);
    }

    static modular factorial(const u32& n) {
        while (factorials.size() <= n)
            factorials.push_back(factorials.back() * modular(static_cast<const i64>(factorials.size())));
        return factorials[n];
    }

    static modular binom(const u32& n, const u32& k) {
        assert(k <= n);
        return factorial(n) / (factorial(k) * factorial(n - k));
    }

    friend modular operator + (modular self, const modular& other) { return self += other; }
    friend modular operator - (modular self, const modular& other) { return self -= other; }
    friend modular operator * (modular self, const modular& other) { return self *= other; }
    friend modular operator / (modular self, const modular& other) { return self /= other; }
    friend modular operator ^ (modular self, const u64& power) { return self ^= power; }

    friend bool operator == (const modular& left, const modular& right) { return left._a == right._a; }
    friend bool operator != (const modular& left, const modular& right) { return left._a != right._a; }
    friend bool operator <= (const modular& left, const modular& right) { return left._a <= right._a; }
    friend bool operator >= (const modular& left, const modular& right) { return left._a >= right._a; }
    friend bool operator <  (const modular& left, const modular& right) { return left._a <  right._a; }
    friend bool operator >  (const modular& left, const modular& right) { return left._a >  right._a; }

    friend bool operator == (const modular& left, const i64& right) { return left._a == right; }
    friend bool operator != (const modular& left, const i64& right) { return left._a != right; }
    friend bool operator <= (const modular& left, const i64& right) { return left._a <= right; }
    friend bool operator >= (const modular& left, const i64& right) { return left._a >= right; }
    friend bool operator <  (const modular& left, const i64& right) { return left._a <  right; }
    friend bool operator >  (const modular& left, const i64& right) { return left._a >  right; }

    friend bool operator == (const i64& left, const modular& right) { return left == right._a; }
    friend bool operator != (const i64& left, const modular& right) { return left != right._a; }
    friend bool operator <= (const i64& left, const modular& right) { return left <= right._a; }
    friend bool operator >= (const i64& left, const modular& right) { return left >= right._a; }
    friend bool operator <  (const i64& left, const modular& right) { return left <  right._a; }
    friend bool operator >  (const i64& left, const modular& right) { return left >  right._a; }

    friend ostream& operator << (std::ostream& stream, const modular& m) {
        return stream << m._a;
    }

    friend std::istream& operator >> (std::istream& stream, modular& m) {
        stream >> m._a;
        m.normalize();
        return stream;
    }
};
template<i64 modulo> vector<modular<modulo>> modular<modulo>::factorials = {1};

using mod = modular<1000000007>;

int main() {
    assert(mod::factorial(10000) == 531950728);
    return 0;
}
