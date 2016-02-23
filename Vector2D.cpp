#include "Vector2D.h"

double Vector2D::Length() const { return sqrtf((float)x*(float)x + (float)y*(float)y); }
double Vector2D::Distance(const Vector2D& vec) const { return sqrtf(((float)vec.x - (float)x)*((float)vec.x - (float)x) + ((float)vec.y - (float)y)*((float)vec.y - (float)y)); }
Vector2D& Vector2D::Normalize() {
	double xxyy = x * x + y * y;
	double invLength = 1.0 / sqrtf((float)xxyy);
	x *= invLength;
	y *= invLength;
	return *this;
}
Vector2D Vector2D::Normal(const Vector2D &a) {
	Vector2D ret = a;
	double xxyy = a.x * a.x + a.y * a.y;
	double invLength = 1.0 / sqrtf((float)xxyy);
	ret.x *= invLength;
	ret.y *= invLength;
	return ret;
}
float Vector2D::Magnitude() { return sqrtf(x * x + y * y); }
float Vector2D::Angle() { return atan2(x, y); }
Vector2D Vector2D::Reflect(const Vector2D & v, const Vector2D &a) {
	Vector2D n = Normal(a);
	float co = -2 * (v.Dot(n) / (n.Magnitude() * n.Magnitude()));
	Vector2D r = {};
	r.x = v.x + co * n.x;
	r.y = r.y + co * n.y;
	return r;
}
Vector2D Vector2D::Project(const Vector2D &b) { return Vector2D(b.x * (x * b.x) / (b.x * b.x), b.y * (y * y) / (b.y * b.y)); }
Vector2D Vector2D::Perp(const Vector2D &a) { return Vector2D(-a.y, a.x); }
Vector2D Vector2D::fromAngle(float a) { return{ cosf(a), sinf(a) }; }
double Vector2D::Dot(const Vector2D& rhs) const { return (x*rhs.x + y*rhs.y); }
double Vector2D::Dot(const Vector2D & a, const Vector2D & b) { return a.x * b.x + a.y * b.y; }
Vector2D Vector2D::operator-() const { return Vector2D(-x, -y); }

Vector2D Vector2D::operator+(const Vector2D& rhs) const { return Vector2D(x + rhs.x, y + rhs.y); }
Vector2D Vector2D::operator-(const Vector2D& rhs) const { return Vector2D(x - rhs.x, y - rhs.y); }
Vector2D& Vector2D::operator+=(const Vector2D& rhs) { x += rhs.x; y += rhs.y; return *this; }
Vector2D& Vector2D::operator-=(const Vector2D& rhs) { x -= rhs.x; y -= rhs.y; return *this; }

Vector2D Vector2D::operator*(const double a) const { return Vector2D(x*a, y*a); }
Vector2D Vector2D::operator*(const Vector2D& rhs) const { return Vector2D(x*rhs.x, y*rhs.y); }
Vector2D& Vector2D::operator*=(const double a) { x *= a; y *= a; return *this; }
Vector2D& Vector2D::operator*=(const Vector2D& rhs) { x *= rhs.x; y *= rhs.y; return *this; }
Vector2D Vector2D::operator/(const double a) const { return Vector2D(x / a, y / a); }
Vector2D& Vector2D::operator/=(const double a) { x /= a; y /= a; return *this; }

bool Vector2D::operator==(const Vector2D& rhs) const { return (x == rhs.x) && (y == rhs.y); }
bool Vector2D::operator!=(const Vector2D& rhs) const { return (x != rhs.x) || (y != rhs.y); }
bool Vector2D::operator<(const Vector2D& rhs) const { return (x < rhs.x && y < rhs.y) ? true : false; }

Vector2D Vector2D::minv(const Vector2D & a, const Vector2D & b) { return (a.x < b.x && a.y < b.y) ? a : b; }
Vector2D Vector2D::maxv(const Vector2D & a, const Vector2D & b) { return (a.x < b.x && a.y < b.y) ? b : a; }
Vector2D Vector2D::clampv(const Vector2D & a, const Vector2D & a_min, const Vector2D & a_max) { return minv(maxv(a, a_min), a_max); }

