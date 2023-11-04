#include "../macros.h"

struct Point3D {
	using d = double;
	d x, y, z;
	explicit Point3D(d x = 0, d y = 0, d z = 0) : x(x), y(y), z(z) {}
	static Point3D polar(d phi, d theta, d r = 1) { // phi = Angle to positive x-axis, theta = Angle to positive z-axis
		return Point3D(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta)) * r;
	}
	auto operator<=>(const Point3D& p) const = default;

#define op(T, O, ex, ey, ez) Point3D& operator O(const T& p) { return x O ex, y O ey, z O ez, *this; }
	op(Point3D, +=, p.x, p.y, p.z)
	op(Point3D, -=, p.x, p.y, p.z)
	op(d, *=, p, p, p)
	op(d, /=, p, p, p)
#undef op
	d operator*(const Point3D& p) const { // Dot Product
		return x * p.x + y * p.y + z * p.z;
	}
	Point3D operator%(const Point3D& p) const { // Cross Product
		return Point3D(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
	}
	Point3D operator-() const { return Point3D() -= *this; }

	Point3D operator+(Point3D p) const { return p += *this; }
	Point3D operator-(const Point3D& p) const { return *this + -p; }
	Point3D operator*(const d& a) const { return Point3D(*this) *= a; }
	Point3D operator/(const d& a) const { return Point3D(*this) /= a; }

	d squareNorm() const { return *this * *this; }
	d norm() const { return sqrt(squareNorm()); }
	Point3D unit() const { return *this / norm(); }
	d phi() const { return atan2(y, x); } // Angle to positive x-axis in [-pi, pi]
	d theta() const { return atan2(y, x); } // Angle to positive z-axis in [0, pi]
	Point3D rotate(double angle, Point3D a) const { // Rotate about axis a CCW (when looking at tip of a)
		a = a.unit();
		double s = sin(angle), c = cos(angle);
		return a * (*this * a) * (1 - c) + *this * c - *this % a * s;
	}
};