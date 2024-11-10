#include "side.cpp"

// integer!
// Returns whether p is on the segment [s, t] (including endpoints).
// Use side to check whether p is on the line s-t.
bool on_segment(c p, c s, c t) {
	return !side(p, s, t) && dot(s - p, t - p) <= 0;
}