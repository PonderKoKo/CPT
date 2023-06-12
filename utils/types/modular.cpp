#include "../macros.h"

#include "../numerical/random.cpp"

template <num m>
struct modular {
	num a;
#define addIfNegative(a, m) a += (a >> 63) & (m)
	constexpr void normalize () {
		a %= m;
		addIfNegative(a, m);
	}

	constexpr modular (const num& x = 0) : a{x} { normalize(); }
	explicit operator num() { return a; };

	modular& operator += (const modular& other) {
		a -= m;
		a += other.a;
		addIfNegative(a, m);
		return *this;
	}

	modular& operator -= (const modular& other) {
		a -= other.a;
		addIfNegative(a, m);
		return *this;
	}

	modular& operator *= (const modular& other) {
		if constexpr(m <= 1ll << 31)
			return a *= other.a, a %= m, *this;
		else
			return a = num(__int128(a) * other.a % m), *this;
	}

	modular operator ! () const {
		// [For m = 9_e + 7, 1 <= a <= 7_e]
		// [2800ms] Clean but slow: return a == 1 ?: -(m / a / modular(m % a));
		// [1020ms] Only for primes: return *this ^ (m - 2);
		// [1985ms] Requires extra code: return modular(euclid(a, m).first);
		return *this ^ (m - 2);
	}

	friend modular operator ^ (modular b, num power) {
		if (power < 0)
			return !b ^ -power;
		modular ans{1};
		for (; power; power >>= 1, b *= b)
			if (power & 1)
				ans *= b;
		return ans;
	}

	friend istream& operator >> (istream& stream, modular& mod) {
		stream >> mod.a;
		mod.normalize();
		return stream;
	}

	modular& operator ++ () { return *this += 1; }
	modular& operator -- () { return *this -= 1; }
	const modular operator ++ (int) { const modular result (*this); ++*this; return result; }
	const modular operator -- (int) { const modular result (*this); --*this; return result; }
	modular operator + () const { return *this; }
	modular operator - () const { return modular(-a); }
	modular& operator /= (const modular& other) { return *this *= !other; }
	modular& operator ^= (const num& power) { return *this = *this ^ power; }
	friend modular operator + (modular self, const modular& other) { return self += other; }
	friend modular operator - (modular self, const modular& other) { return self -= other; }
	friend modular operator * (modular self, const modular& other) { return self *= other; }
	friend modular operator / (modular self, const modular& other) { return self /= other; }
	auto operator<=>(const modular& other) const = default;
	friend ostream& operator << (ostream& stream, const modular& mod) { return stream << mod.a; }

	// Combinatorics
	static vector<modular> factorials;

	static modular factorial(const num& n) {
		factorials.reserve(n);
		for (static num i = 1; i <= n; i++)
			factorials.push_back(factorials[i-1] * i);
		return factorials[n];
	}

	static modular binom(const num& n, const num& k) {
		return factorial(n) / factorial(k) / factorial(n - k);
	}

	static vector<modular> inverses(const vector<modular>& x) {
		modular denominator = !reduce(all(x), modular(1), multiplies<>());
		vector<modular> prefix(size(x)), suffix(size(x)), ans(size(x));
		exclusive_scan(all(x), begin(prefix), modular(1), multiplies<>());
		exclusive_scan(rbegin(x), rend(x), rbegin(suffix), modular(1), multiplies<>());
		transform(all(prefix), begin(suffix), begin(ans), multiplies<>());
		transform(all(ans), begin(ans), [&] (modular z) { return z * denominator; });
		return ans;
	}

	// Polynomial Hashes
	static const modular base;
	modular(const seq& s) : a{accumulate(rbegin(s), rend(s), modular(0), [](modular acc, const auto& x) { return acc * base + x; })} {}
	modular(num i, num x) : a{x * (base ^ i)} {}
	modular& operator>>= (num i) { return *this *= base ^ i; }
	modular& operator<<= (num i) { return *this >>= -i; }
	friend modular operator>> (modular self, num i) { return self >>= i; }
	friend modular operator<< (modular self, num i) { return self <<= i; }
	struct Hash { num operator() (modular r) const { return num(r); } };

#undef addIfNegative
};
template<num m> vector<modular<m>> modular<m>::factorials = {1};
template<num m> modular<m> const modular<m>::base{uniform_int_distribution<num>(3_e, 9_e)(rng)};

// using mod = modular<9_e + 7>;
// using mod = modular<998'244'353>;
// using hashmod = modular<4'611'686'018'427'387'847ll>;
