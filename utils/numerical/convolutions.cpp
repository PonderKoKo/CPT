#include "../types/mint.cpp"

template<auto t>
auto convolve(auto a, auto b) {
    t(a, 1), t(b, 1);
    rep(i, size(a)) a[i] *= b[i];
    return t(a, 0), a;
}

void AND(vector<mint>& a, bool b) {
    for (int s = 1; s < size(a); s *= 2)
        rep(i, size(a)) if (i & s)
            a[i ^ s] += (b ?: -1) * a[i];
}

void OR(vector<mint>& a, bool b) {
    if (b) reverse(all(a)), AND(a, b);
    else AND(a, b), reverse(all(a));
}

void XOR(vector<mint>& a, bool b) {
    for (int s = 1; s < size(a); s *= 2)
        rep(i, size(a))
            a[i] = a[i ^ s] + a[i] * (i & s ? -2 : 1);
    if (!b) for (auto& x: a) x /= size(a);
}

void GCD(vector<mint>& a, bool b) {
    rep(u, ssize(a) - 1) {
        int i = b ? u + 1: size(a) + ~u;
        for (int j = 2 * i; j < size(a); j += i)
            a[i] += a[j] * (b ?: -1);
    }
}

void MAX(vector<mint>& a, bool b) {
    if (b) partial_sum(all(a), begin(a));
    else adjacent_difference(all(a), begin(a));
}

void MIN(vector<mint>& a, bool b) {
    if (b) reverse(all(a)), MAX(a, b);
    else MAX(a, b), reverse(all(a));
}

// TODO Deal with sizes more elegantly. Merge with sos / zeta transform? Add Mobius Transform and Subset Sum Convolution
