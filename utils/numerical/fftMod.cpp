#include "fft.cpp"

seq convolve(const seq &a, const seq &b, num m) {
    if (empty(a) || empty(b))
        return seq{};
    seq c(size(a) + size(b) - 1);
    num n = 2 * bit_floor(size(c)), cut = num(sqrt(m));
    vector<cd> l(n), r(n), outs(n), outl(n);
    rep(i,ssize(a))
        l[i] = cd(double(a[i] / cut), double(a[i] % cut));
    rep(i,ssize(b))
        r[i] = cd(double(b[i] / cut), double(b[i] % cut));
    fft(l), fft(r);
    rep(i,n) {
        num j = -i & (n - 1);
        outl[j] = (l[i] + conj(l[j])) * r[i] / (double(2 * n));
        outs[j] = (l[i] - conj(l[j])) * r[i] / (double(2 * n)) / 1i;
    }
    fft(outl), fft(outs);
    rep(i,ssize(c)) {
        num av = num(real(outl[i])+.5), cv = num(imag(outs[i])+.5);
        num bv = num(imag(outl[i])+.5) + num(real(outs[i])+.5);
        c[i] = ((av % m * cut + bv) % m * cut + cv) % m;
    }
    return c;
}