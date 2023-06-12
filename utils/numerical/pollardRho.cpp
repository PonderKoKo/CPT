#include "../macros.h"

num modmul(num a, num b, num mod) {
	return num(__int128(a) * b % mod);
}
num modpow(num b, num e, num mod) {
	num ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1)
			ans = modmul(ans, b, mod);
	return ans;
}

bool isPrime(num n) {
	if (n < 2 || n % 6 % 4 != 1)
		return (n | 1) == 3;
	seq A{2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	num s = __builtin_ctzll(n - 1), d = n >> s;
	for (num a : A) {
		num p = modpow(a % n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s)
			return false;
	}
	return true;
}

num pollard(num n) {
	auto f = [n] (num x) { return modmul(x, x, n) + 1; };
	num x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while (t++ % 40 || gcd(prd, n) == 1) {
		if (x == y)
			x = ++i, y = f(x);
		if ((q = modmul(prd, max(x,y) - min(x,y), n)))
			prd = q;
		x = f(x), y = f(f(y));
	}
	return gcd(prd, n);
}
seq factor(num n) {
	if (n == 1) return seq{};
	if (isPrime(n)) return seq{n};
	num x = pollard(n);
	seq l = factor(x), r = factor(n / x);
	l.insert(end(l), all(r));
	return l;
}