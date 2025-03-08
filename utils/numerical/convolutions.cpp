#include "../types/mint.cpp"

#define convolve(op, x, y) [] (auto a, auto b) { op<1>(a), op<1>(b); rep(i, size(a)) a[i] *= b[i]; return op<0>(a), a; } (x, y);

template<bool b>
void AND(auto& a) { // AND<1>(a) is sum over supersets
    for (int s = 1; s < size(a); s *= 2)
        rep(i, size(a)) if (i & s)
            a[i ^ s] += (b ?: -1) * a[i];
}

template<bool b>
void OR(auto& a) { // OR<1>(a) is sum over subsets
    for (int s = 1; s < size(a); s *= 2)
        rep(i, size(a)) if (i & s)
            a[i] += (b ?: -1) * a[i ^ s];
}

template<bool b>
void XOR(auto& a) {
    for (int s = 1; s < size(a); s *= 2)
        rep(i, size(a))
            a[i] = a[i ^ s] + a[i] * (i & s ? -2 : 1);
    if (!b) for (auto& x: a) x /= size(a);
}

template<bool b>
void GCD(auto& a) {
    rep(u, ssize(a) - 1) {
        int i = b ? u + 1: size(a) + ~u;
        for (int j = 2 * i; j < size(a); j += i)
            a[i] += a[j] * (b ?: -1);
    }
}

template<bool b>
void MAX(auto& a) {
    if (b) partial_sum(all(a), begin(a));
    else adjacent_difference(all(a), begin(a));
}

template<bool b>
void MIN(auto& a) {
    if (b) reverse(all(a)), MAX(a, b);
    else MAX(a, b), reverse(all(a));
}

void odd_negation(auto& a) { // odd_negation(a)[i] = (-1)^popcount(i) * a[i]
    rep(i, size(a) / 2) a[2 * i + (1 & ~popcount(ull(i)))] *= -1;
}

void mobius(auto& a) { // mobius(a)[i] = sum_(i' subseteq i) (-1)^popcount(i' - i) * a[i]
    odd_negation(a), OR<1>(a), odd_negation(a);
}
