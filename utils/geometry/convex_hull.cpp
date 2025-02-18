#include "complex.cpp"

vector<c> convex_hull(vector<c> v) {
    if (size(v) < 2) return v;
    sort(all(v));
    vector<c> h(size(v) + 1);
    int s = 0, t = -1;
    for (int i = 2; i--; s = t--, reverse(all(v))) {
        for (c a : v) {
            while (s < t-- && cross(h[t + 1] - h[t], a - h[t]) <= 0);
            h[t += 2] = a;
        }
    }
    return {begin(h), begin(h) + t + (h[0] != h[1])};
}
