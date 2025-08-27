#include "complex.cpp"

// Returns sign for side of p relative to line st.
//   +1
// s--0--t
//   -1
int side(c p, c s, c t) {
    d x = cross(t - s, p - s);
    return (x > 0) - (x < 0);
}

// Returns whether p is on the segment [s, t] (including endpoints).
// Use side to check whether p is on the line s-t.
bool on_segment(c p, c s, c t) {
    return !side(p, s, t) && dot(s - p, t - p) <= 0;
}

// Returns whether the segments [s-t] and [p-q] have a common point.
bool segment_intersection(c s, c t, c p, c q) {
    return on_segment(p,s,t) || on_segment(q,s,t) || on_segment(s,p,q) || on_segment(t,p,q) ||
        side(p,s,t) != side(q,s,t) && side(s,p,q) != side(t,p,q);
}

// Returns twice the area of polygon a (CW or CCW).
d polygon_area(const vector<c>& a) {
    d ans = 0;
    for (c x = a.back(); c y : a)
        ans += cross(x, y), x = y;
    return abs(ans);
}

