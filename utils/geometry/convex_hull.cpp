#include "complex.cpp"

vector<c> convex_hull(vector<c> v) {
    if (size(v) < 2) return v;
    sort(all(v));
    vector<c> h(size(v) + 1);
    int s, t = 0;
    rep(i, 2) {
        s = t--;
        for (c a : v) {
            while (s < t-- && cross(h[t + 1] - h[t], a - h[t]) <= 0);
            h[t += 2] = a;
        }
        reverse(all(v));
    }
    return {begin(h), begin(h) + t - (h[0] == h[1])};
}
