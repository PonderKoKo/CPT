#include "complex.cpp"

vector<c> convex_hull(vector<c> v) {
    if (size(v) < 2) return v;
    sort(all(v));
    c h[size(v) + 1], *t = h;
    rep(i, 2) {
        for (c *s = t--; c a : v) {
            while (s < t-- && cross(t[1] - *t, a - *t) <= 0);
            *++++t = a;
        }
        reverse(all(v));
    }
    return {h, t - (*h == h[1])};
}
