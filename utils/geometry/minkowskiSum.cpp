#include "../macros.h"

/* Minkowski Sum of Two Polygons
 * Complexity: O(n + m)
 * Requires polygons to be given in ccw order.
 * Input Numbers are multiplied so T must leave room for this
 * Tested for Integer Type
 */
template<typename T>
vector<complex<T>> minkowskiSum(vector<complex<T>> p, vector<complex<T>> q) {
    auto normalize = [&] (vector<complex<T>>& w) {
        int j = 0;
        for (int i = 1; i < ssize(w); i++)
            if (pair(w[i].imag(), w[i].real()) < pair(w[j].imag(), w[j].real()))
                j = i;
        rotate(begin(w), begin(w) + j, end(w));
        rep(i, 2)
            w.push_back(w[i]);
    };
    normalize(p), normalize(q);
    vector<complex<T>> w;
    for (int i = 0, j = 0; i < ssize(p) - 2 || j < ssize(q) - 2;) {
        w.push_back(p[i] + q[j]);
        T cross = (conj(p[i+1] - p[i]) * (q[j+1] - q[j])).imag();
        if (cross >= 0 && i < ssize(p) - 2)
            i++;
        if (cross <= 0 && j < ssize(q) - 2)
            j++;
    }
    return w;
}
