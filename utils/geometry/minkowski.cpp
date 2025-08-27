#include "complex.cpp"

/* Minkowski Sum of Two Convex Polygons
 * Complexity: O(n + m)
 * Requires polygons to be given in ccw order.
 * Input Numbers are multiplied so T must leave room for this
 */
vector<c> minkowski(vector<c> p, vector<c> q) {
    vector<c> w;
    int i = max_element(all(p)) - begin(p), j = max_element(all(q)) - begin(q);
    do {
        w.push_back(p[i] + q[j]);
        d x = cross(p[(i + 1) % size(p)] - p[i], q[(j + 1) % size(q)] - q[j]);
        i += x >= 0;
        j += x <= 0;
    } while (w[0] != p[i %= size(p)] + q[j %= size(q)]);
    return w;
}

// https://acm.timus.ru/problem.aspx?space=1&num=1894