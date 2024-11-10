#include "complex.cpp"

/* Minkowski Sum of Two Polygons
 * Complexity: O(n + m)
 * Requires polygons to be given in ccw order.
 * Input Numbers are multiplied so T must leave room for this
 * Untested
 */
vector<c> minkowski(vector<c> p, vector<c> q) {
	for (auto z : {&p, &q})
		ranges::rotate(*z, ranges::max_element(*z, lo));
	vector<c> w;
	for (int i = 0, j = 0; i < size(p) || j < size(q);) {
		w.push_back(p[i] + q[j]);
		d x = cross(p[(i + 1) % size(p)] - p[i], q[(j + 1) % size(q)] - q[j]);
		i += x >= 0 && i < size(p);
		j += x <= 0 && j < size(q);
	}
	return w;
}
