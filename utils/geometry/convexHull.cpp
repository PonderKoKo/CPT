#include "../macros.h"

// Completely untested, largely copied from kactl
template<typename T>
vector<complex<T>> convexHull(vector<complex<T>> v) {
    if (ssize(v) <= 1)
        return v;
    sort(all(v), [] (auto a, auto b) {
        return pair(a.real(), a.imag()) < pair(b.real(), b.imag());
    });
    vector<complex<T>> h(size(v) + 1);
    int s{0}, t{0};
    for (int i{2}; i--; s = --t, reverse(all(v))) {
        for (const auto& a : v) {
            while (t > s + 1 && (conj(h[t - 1] - h[t - 2]) * (a - h[t - 2])).imag() <= 0)
                t--;
            h[t++] = a;
        }
    }
    return {begin(h), begin(h) + t - (t == 2 && h[0] == h[1])};
}