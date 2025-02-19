#include "../types/mint.cpp"

mint fac(int n) {
	static vector<mint> b{1};
	for (static int i = 1; i <= n; i++)
		b.push_back(b.back() * i);
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

mint binom(int n, int k) {
	return k < 0 || k > n ? 0 : fac(n) * ifac(k) * ifac(n - k);
}
