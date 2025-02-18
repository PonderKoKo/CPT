#include "complex.cpp"

pair<c,c> closest_pair(vector<c> a) {
    set<c> s;
    ranges::sort(a, lo);
    pair<d,pair<c,c>> ans{LLONG_MAX, {}};
    for (int j = 0; c p : a) {
        d x = 1 + sqrt(ans.first);
        while (imag(a[j]) <= imag(p) - x) s.erase(a[j++]);
        for (auto lo = s.lower_bound(p - x), hi = s.upper_bound(p + x); lo != hi; ++lo)
            ans = min(ans, {norm(*lo - p), {*lo, p}});
        s.insert(p);
    }
    return ans.second;
}
