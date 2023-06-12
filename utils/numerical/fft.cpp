#include "../macros.h"

typedef complex<double> cd;

void fft(vector<cd>& a) {
    num n = ssize(a), L = bit_width(size(a)) - 1;
    static vector<complex<long double>> R(2, 1);
    static vector<cd> rt(2, 1);  // (^ 10% faster if double)
    for (static num k = 2; k < n; k *= 2) {
        R.resize(n); rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        for (num i = k; i < 2 * k; i++)
            rt[i] = R[i] = i & 1 ? R[i/2] * x : R[i/2];
    }
    seq rev(n);
    rep(i,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, k) {
                // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
                auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
                cd z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}

seq convolve(const seq& a, const seq& b) {
    seq c(size(a) + size(b) - 1);
    num n = 2 * bit_floor(size(c));
    vector<cd> in(n), out(n);
    copy(all(a), begin(in));
    rep(i,ssize(b))
        in[i].imag(b[i]);
    fft(in);
    for (cd& x : in)
        x *= x;
    rep(i,n)
        out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    rep(i,ssize(c))
        c[i] = llround(imag(out[i]) / 4 / n);
    return c;
}

vector<cd> convolve(const vector<cd>& a, const vector<cd>& b) {
    num s = ssize(a) + ssize(b) - 1;
    num n = 2 * bit_floor(static_cast<unsigned long long>(s));
    vector<cd> x(a), y(b), out(n);
    x.resize(n), y.resize(n);
    fft(x), fft(y);
    rep(i, n)
        out[-i & (n - 1)] = x[i] * y[i] / cd(n);
    fft(out);
    return {begin(out), begin(out) + s};
}
