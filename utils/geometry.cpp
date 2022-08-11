#include "macros.h"

template<typename coordinate>
struct Vector {
    coordinate x, y;
    Vector(coordinate a = 0, coordinate b = 0) : x(a), y(b) {}
    static inline Vector null = Vector(0, 0);

    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }
    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }
    Vector operator*(const coordinate& k) const {
        return Vector(x * k, y * k);
    }
    friend Vector operator*(const coordinate& k, const Vector& v) {
        return Vector(k * v.x, k * v.y);
    }

    /* Dot Product
     * a dot b = a.norm() * b.norm() * cos(angle)
     * < 0 : obtuse angle
     * = 0 : right angle
     * > 0 : acute angle
     */
    coordinate operator * (const Vector& other) const {
        return x * other.x + y * other.y;
    }
    /* Cross Product
     * a cross b = a.norm() * b.norm() * sin(angle)
     * < 0 : clockwise
     * = 0 : collinear
     * > 0 : counterclockwise
     */
    coordinate operator % (const Vector& other) const {
        return x * other.y - y * other.x;
    }
    Vector operator - () const {
        return Vector(-x, -y);
    }



    friend std::istream& operator >> (std::istream& stream, Vector& u) {
        return stream >> u.x >> u.y;
    }

    bool operator == (const Vector& other) const {
        return x == other.x && y == other.y;
    }
    bool operator != (const Vector& other) const {
        return !(*this == other);
    }
    bool operator < (const Vector& other) const {
        return make_pair(x, y) < make_pair(other.x, other.y);
    }

    bool operator > (const Vector& other) const {
        return other < *this;
    }

    enum class angle {
        zero,
        acute,
        right,
        obtuse,
        straight,
        acute_reflex,
        right_reflex,
        obtuse_reflex,
        undefined
    };

    // Counterclockwise Angle
    angle operator ^ (const Vector& other) const {
        if (*this == null || other == null)
            return angle::undefined;
        i64 dot = *this * other;
        i64 cross = *this % other;
        if (cross == 0) {
            if (dot > 0)
                return angle::zero;
            else /* dot < 0 ### = 0 is impossible */
                return angle::straight;
        } else if (cross > 0) {
            if (dot < 0)
                return angle::obtuse;
            else if (dot == 0)
                return angle::right;
            else /* dot > 0 */
                return angle::acute;
        } else {
            if (dot < 0)
                return angle::acute_reflex;
            else if (dot == 0)
                return angle::right_reflex;
            else /* dot > 0 */
                return angle::obtuse_reflex;
        }
        assert(0);
    }

    friend bool angle_interval(angle lo, angle hi, angle a, bool lo_inclusive = true, bool hi_inclusive = false) {
        if (lo == angle::undefined || hi == angle::undefined || a == angle::undefined)
            return false;
        if (lo <= hi) {
            if (lo_inclusive) {
                if (hi_inclusive)
                    return lo <= a && a <= hi;
                else
                    return lo <= a && a < hi;
            } else {
                if (hi_inclusive)
                    return lo < a && a <= hi;
                else
                    return lo < a && a < hi;
            }
        } else {
            if (lo_inclusive) {
                if (hi_inclusive)
                    return lo <= a || a <= hi;
                else
                    return lo <= a || a < hi;
            } else {
                if (hi_inclusive)
                    return lo < a || a <= hi;
                else
                    return lo < a || a < hi;
            }
        }
    }

    // Square Norm, just Dot Product with itself
    [[nodiscard]] coordinate square_norm() const {
        return x * x + y * y;
    }

    [[nodiscard]] coordinate manhattan_norm() const {
        return abs(x) + abs(y);
    }

    /*
    // Counterclockwise Angle (not sure if this is even correct)
    double operator ^ (const Vector<double>& other) const {
        return atan2(*this % other, *this * other);
    } */

    [[nodiscard]] double distanceToLine(const Vector<double>& a, const Vector<double>& b) const {
        Vector<double> ab = b - a;
        Vector<double> ac = *this - a;
        return abs(ac % ab) / sqrt(ab.square_norm());
    }

    // Rotates Counterclockwise, works with negative angles
    [[nodiscard]] Vector rotate(double angle) const {
        return Vector<double>(x * cos(angle) + y * sin(angle), -x * sin(angle) + y * cos(angle));
    }
};

/* https://cp-algorithms.com/geometry/nearest_points.html
 * Complexity O(n log n)
 * Returns the square distance of the two closest points.
 */
template<typename coordinate>
coordinate closest_pair(vector<Vector<coordinate>> points) {
    sort(all(points));
    vector<Vector<coordinate>> buffer(points.size());
    return closest_pair(0, points.size(), points, buffer);
}

template<typename coordinate>
coordinate closest_pair(u32 l, u32 r, vector<Vector<coordinate>> &points, vector<Vector<coordinate>> &buffer) {
#define SOME(a, l, r) next((a).begin(), l), next((a).begin(), r)
#define UPDATE(x) min_sqr_dist = min(min_sqr_dist, x)
#define SQUARE(a) ((a) * (a))
#define CMP_Y [] (const Vector<coordinate>& a, const Vector<coordinate>& b) { return a.y < b.y; }
    coordinate min_sqr_dist = numeric_limits<coordinate>::max();
    if (r - l <= 3) {
        for (u32 i = l; i < r; ++i)
            for (u32 j = i + 1; j < r; ++j)
                UPDATE((points[i] - points[j]).square_norm());
        sort(SOME(points, l, r), CMP_Y);
        return min_sqr_dist;
    }
    u32 mid = (l + r) / 2;
    i64 mid_x = points[mid].x;
    UPDATE(closest_pair(l, mid, points, buffer));
    UPDATE(closest_pair(mid, r, points, buffer));
    merge(SOME(points, l, mid), SOME(points, mid, r), buffer.begin(), CMP_Y);
    copy(SOME(buffer, 0, r - l), points.begin() + l);
    i32 tsz = 0;
    for (u32 i = l; i < r; ++i) {
        if (SQUARE(points[i].x - mid_x) < min_sqr_dist) {
            for (i32 j = tsz - 1; j >= 0 && SQUARE(points[i].y - buffer[j].y) < min_sqr_dist; --j)
                UPDATE((points[i] - buffer[j]).square_norm());
            buffer[tsz++] = points[i];
        }
    }
    return min_sqr_dist;
#undef SOME
#undef UPDATE
#undef SQUARE
#undef CMP_Y
}

/* Monotone Chain Algorithm for Convex Hull
 * Complexity O(n log n)
 * https://cp-algorithms.com/geometry/convex_hull.html
 * Assuming points are pairwise distinct
 */
template<typename coordinate>
void convex_hull(vector<Vector<coordinate>>& a, bool include_collinear = false) {
using angle = typename Vector<coordinate>::angle;
    if (a.size() == 1)
        return;

    sort(a.begin(), a.end());
    auto p1 = a[0], p2 = a.back();
    vector<Vector<coordinate>> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (u32 i = 1; i < a.size(); ++i) {
        angle theta = (a[i] - p1) ^ (p2 - p1);
        assert(theta != angle::undefined);
        if (i == a.size() - 1 || angle_interval(angle::straight, angle::zero, theta, include_collinear, include_collinear)) {
            while (up.size() >= 2 && angle_interval(angle::zero, angle::straight, (up[up.size() - 1] - up[up.size() - 2]) ^ (a[i] - up[up.size() - 2]), !include_collinear, !include_collinear))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || angle_interval(angle::zero, angle::straight, theta, include_collinear, include_collinear)) {
            while (down.size() >= 2 && angle_interval(angle::straight, angle::zero, (down[down.size() - 1] - down[down.size() - 2]) ^ (a[i] - down[down.size() - 2]), !include_collinear, !include_collinear))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    // Everything is on a line and both up and down are identical.
    if (include_collinear && up.size() == a.size()) {
        reverse(a.begin(), a.end());
        return;
    }
    a.clear();
    // Don't use start and end from up and down, because they are the same.
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
}

/* Shoelace Formula
 * Complexity O(n)
 * Returns double the area to respect integer types.
 */
template<typename coordinate>
coordinate double_area(const vector<Vector<coordinate>>& a) {
    coordinate area = 0;
    for (u32 i = 0; i < a.size(); ++i)
        area += a[i] % a[(i + 1) % a.size()];
    return abs(area);
}

int main() {
    vector<Vector<i64>> points = {{0, 0}, {4, 1}, {5, 4}, {2, 2}};
    vector<Vector<i64>> points2 = {{4,1}, {7,3}, {5,5}, {2,4}, {4,3}};

    assert(closest_pair(points) == 5 && "Closest Pair on DiscreteVector");
    assert(double_area(points) == 13 && "Shoelace Formula on DiscreteVector — 1");
    assert(double_area(points2) == 17 && "Shoelace Formula on DiscreteVector — 2");
    return 0;
}