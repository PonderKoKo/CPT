#include "macros.h"

template <num Modulo>
class modular {
    static_assert(Modulo > 0, "Modulo must be positive");
private:
    static vector<modular> factorials;
    num _a;
    const num _m = Modulo;

    void normalize () {
        if (_a >= _m || -_a <= _m)
            _a %= _m;
        if (_a < 0)
            _a += _m;
    }

public:
    modular (const modular& m = modular(0)) : _a(m._a) { }
    modular (const num& a) : _a (a) { normalize(); }
    explicit operator num() { return _a; };

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

    modular& operator *= (const modular& other) { return _a *= other._a, normalize(), *this; }

    modular& operator /= (const modular& other) { return *this *= !other; }

    modular& operator ^= (num power) {
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
    modular operator ! () const { return *this ^ (_m - 2); }

    static modular factorial(const num& n) {
        assert(0 <= n);
        while (factorials.size() <= n)
            factorials.push_back(factorials.back() * modular(static_cast<const num>(factorials.size())));
        return factorials[n];
    }

    static modular binom(const num& n, const num& k) {
        return factorial(n) / (factorial(k) * factorial(n - k));
    }

    friend modular operator + (modular self, const modular& other) { return self += other; }
    friend modular operator - (modular self, const modular& other) { return self -= other; }
    friend modular operator * (modular self, const modular& other) { return self *= other; }
    friend modular operator / (modular self, const modular& other) { return self /= other; }
    friend modular operator ^ (modular self, const num& power) { return self ^= power; }

    friend ostream& operator << (ostream& stream, const modular& m) { return stream << m._a; }

    friend istream& operator >> (istream& stream, modular& m) {
        stream >> m._a;
        m.normalize();
        return stream;
    }
};
template<num modulo> vector<modular<modulo>> modular<modulo>::factorials = {1};

using mod = modular<998'244'353>;

int main() {
    assert(modular<1'000'000'007>::factorial(10000) == 531950728);
    return 0;
}
