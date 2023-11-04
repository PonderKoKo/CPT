#include "../macros.h"

struct infinum {
    static const infinum infty() { return infinum(1, 0); }
    static const infinum negty() { return infinum(-1, 0); }
    num i, x;
    infinum(num z) : i(0), x(z) {}
    infinum(num j, num z) : i(j), x(z) { normalize(); }
    explicit operator num() {
        assert(!i);
        return x;
    }
    void normalize() {
        if (i)
            x = 0, i = sign(i);
    }
    infinum& operator += (const infinum& other) {
        assert(i * other.i != -1);
        i += other.i;
        x += other.x;
        return *this;
    }

    infinum& operator -= (const infinum& other) {
        return *this += -other;
    }

    friend infinum operator * (infinum self, const infinum& other) {
        if (self.i || other.i) {
            assert(sign(self) * sign(other) != 0);
            return infinum(sign(self) * sign(other), 0);
        }
        return infinum(self.x * other.x);
    }


    infinum& operator *= (const infinum& other) {
        return *this = *this * other;
    }

    friend infinum operator / (infinum self, const infinum& other) {
        assert(!self.i || !other.i);
        if (self.i)
            return infinum(sign(self) * sign(other), 0);
        else if (other.i)
            return infinum(0);
        else
            return infinum(self.x / other.x);
    }


    infinum& operator /= (const infinum& other) {
        return *this = *this / other;
    }

    friend istream& operator >> (istream& stream, infinum& inf) {
        inf.i = 0;
        stream >> inf.x;
        inf.normalize();
        return stream;
    }

    infinum& operator ++ () { return *this += 1; }
    infinum& operator -- () { return *this -= 1; }
    const infinum operator ++ (int) { const infinum result (*this); ++*this; return result; }
    const infinum operator -- (int) { const infinum result (*this); --*this; return result; }
    infinum operator + () const { return *this; }
    infinum operator - () const { return infinum(-i, -x); }
    friend infinum operator + (infinum self, const infinum& other) { return self += other; }
    friend infinum operator - (infinum self, const infinum& other) { return self -= other; }
    auto operator<=>(const infinum& other) const = default;
    friend ostream& operator << (ostream& stream, const infinum& inf) {
        switch (sign(inf.i)) {
            case -1:
                stream << "NEGTY";
                break;
            case 0:
                stream << inf.x;
                break;
            case 1:
                stream << "INFTY";
                break;
        }
        return stream;
    }
};
