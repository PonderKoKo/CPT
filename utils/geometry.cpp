#include "macros.h"

template<typename coordinate>
struct Vector {
    coordinate x, y;
    Vector(coordinate a = 0, coordinate b = 0) : x(a), y(b) {}
    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }
    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }
    Vector operator*(const coordinate& k) const {
        return Vector(x * k, y * k);
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
    coordinate operator % (const Vector& other) const { // cross product
        return x * other.y - y * other.x;
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
        return x < other.x || (x == other.x && y < other.y);
    }
    Vector operator - () const {
        return Vector(-x, -y);
    }

    [[nodiscard]] coordinate square_norm() const {
        return x * x + y * y;
    }

    [[nodiscard]] double norm() const {
        return sqrt(x * x + y * y);
    }

    [[nodiscard]] double distanceToLine(const Vector& a, const Vector& b) const {
        Vector ab = b - a;
        Vector ac = *this - a;
        return abs(ac % ab) / ab.norm();
    }

    [[nodiscard]] double distanceToPoint(const Vector& p) const {
        return (*this - p).norm();
    }
};

// https://cp-algorithms.com/geometry/nearest_points.html
// This only returns the minimum square distance but can easily be altered
// Points needs to be passed in presorted by x coordinate, l = 0, r = n
template<typename coordinate>
i64 closest_pair(u32 l, u32 r, vector<Vector<coordinate>> &points, vector<Vector<coordinate>> &buffer) {
#define threshold 3
#define SOME(a, l, r) (a).begin() + (l), (a).begin() + (r)
#define update(x) min_square_dist = min(min_square_dist, x)
#define SQUARE(a) ((a) * (a))
#define CMP_Y [] (const Vector<coordinate>& a, const Vector<coordinate>& b) { return a.y < b.y; }
    i64 min_square_dist = 1'000'000'000'000'000'000;
    if (r - l <= threshold) {
        for (u32 i = l; i < r; ++i)
            for (u32 j = i + 1; j < r; ++j)
                update((points[i] - points[j]).square_norm());
        sort(SOME(points, l, r), CMP_Y);
        return min_square_dist;
    }
    u32 mid = (l + r) / 2;
    i64 mid_x = points[mid].x;
    update(closest_pair(l, mid, points, buffer));
    update(closest_pair(mid, r, points, buffer));
    merge(SOME(points, l, mid), SOME(points, mid, r), buffer.begin(), CMP_Y);
    copy(SOME(buffer, 0, r - l), points.begin() + l);
    i32 tsz = 0;
    for (u32 i = l; i < r; ++i) {
        if (SQUARE(points[i].x - mid_x) < min_square_dist) {
            for (i32 j = tsz - 1; j >= 0 && SQUARE(points[i].y - buffer[j].y) < min_square_dist; --j)
                update((points[i] - buffer[j]).square_norm());
            buffer[tsz++] = points[i];
        }
    }
    return min_square_dist;
#undef threshold
#undef SOME
#undef update
#undef SQUARE
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.precision(10);
    { // Closest Pair
        vector<Vector<i64>> points = {{0, 0}, {5, 4}, {2, 2}, {4, 1}};
        sort(ALL(points));
        vector<Vector<i64>> buffer(points.size());
        assert(closest_pair(0, points.size(), points, buffer) == 5);
    }
    
    return 0;
}