#include "../types/mint.cpp"

mint fac(int n) {
	static vector<mint> b{1};
	for (static int i = 0; i < n;)
		b.push_back(b.back() * ++i);
	return b[n];
}

mint ifac(int n) {
	static vector<mint> b{1};
	for (static int i = 1; i <= n; i *= 2) {
		b.resize(2 * i);
		b.back() = !fac(2 * i - 1);
		for (int j = 2 * i; --j > i;)
			b[j - 1] = b[j] * j;
	}
	return b[n];
}

mint binom(num n, num k) {
	return k < 0 || k > n ? 0 : fac(n) * ifac(k) * ifac(n - k);
}

/* Number of
 * balanced bracket sequences with n pairs
 * binary trees with n + 1 leaves (each vertex has 0 or 2 children)
*/
mint catalan(int n) {
    return fac(2 * n) * ifac(n) * ifac(n + 1);
}
