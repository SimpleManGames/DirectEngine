#include "Vector3D.h"
#include "Matrix3D.h"
#include "Matrix2D.h"

Vector3D Vector3D::ZeroVector() { return Vector3D(0.0f, 0.0f, 0.0f); }

double Vector3D::Length() const { return sqrtf((float)x * (float)x + (float)y * (float)y + (float)z * (float)z); }
double Vector3D::Distance(const Vector3D & vec) const
{
	return sqrtf(((float)vec.x - (float)x)*((float)vec.x - (float)x) + ((float)vec.y - (float)y)*((float)vec.y - (float)y) + ((float)vec.z - (float)z)*((float)vec.z - (float)z));
}
double Vector3D::Dot(const Vector3D & vec) const { return (x * vec.x + y * vec.y + z * vec.z); }
double Vector3D::Dot(const Vector3D & a, const Vector3D & b) { return (a.x * b.x + a.y * b.y + a.z * b.z); }
Vector3D& Vector3D::Normalize()
{
	double xxyyzz = x * x + y * y + z * z;
	double invLength = 1.0 / sqrtf((float)xxyyzz);
	x *= (float)invLength;
	y *= (float)invLength;
	z *= (float)invLength;
	return *this;
}
Vector3D Vector3D::Normal(const Vector3D & a)
{
	Vector3D ret;
	double xxyyzz = a.x * a.x + a.y * a.y + a.z * a.z;
	double invLength = 1.0 / sqrtf((float)xxyyzz);
	ret.x *= (float)invLength;
	ret.y *= (float)invLength;
	ret.z *= (float)invLength;
	return ret;
}
float Vector3D::Magnitude() { return sqrtf(x * x + y * y + z * z); }
Vector3D Vector3D::Reflect(const Vector3D & v, const Vector3D & a) {
	Vector3D n = Normal(a);
	float co = -2 * (v.Dot(n) / (n.Magnitude() * n.Magnitude()));
	Vector3D r = {};
	r.x = v.x + co * n.x;
	r.y = r.y + co * n.y;
	r.z = r.z + co * n.z;
	return r;
}

Vector3D Vector3D::Project(const Vector3D & b) { return Vector3D(b.x * (x * b.x) / (b.x * b.x), b.y * (y * y) / (b.y * b.y), b.z * (z * b.z) / (b.x * b.x)); }

Vector3D Vector3D::operator-() const { return Vector3D(-x, -y, -z); }
Vector3D Vector3D::operator+(const Vector3D & rhs) const { return Vector3D(x + rhs.x, y + rhs.y, z + rhs.z); }
Vector3D Vector3D::operator-(const Vector3D & rhs) const { return Vector3D(x - rhs.x, y - rhs.y, z - rhs.z); }
Vector3D & Vector3D::operator+=(const Vector3D & rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
Vector3D & Vector3D::operator-=(const Vector3D & rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this; }
Vector3D Vector3D::operator*(const double scale) const { return Vector3D(x * scale, y * scale, z * scale); }
Vector3D Vector3D::operator*(const Vector3D & rhs) const { return Vector3D(x * rhs.x, y * rhs.y, z * rhs.z); }
Vector3D & Vector3D::operator*=(const double scale) { x *= (float)scale; y *= (float)scale; z *= (float)scale; return *this; }
Vector3D & Vector3D::operator*=(const Vector3D & rhs) { x *= rhs.x; y *= rhs.y; z *= rhs.z; return *this; }
Vector3D Vector3D::operator/(const double scale) const { return Vector3D(x / scale, y / scale, z / scale); }
Vector3D & Vector3D::operator/=(const double scale) { x /= (float)scale; y /= (float)scale; z /= (float)scale; return *this; }
Vector3D Vector3D::operator*(const Matrix3D & a) {
	return Vector3D((x * a.mm[0][0]) + (y * a.mm[1][0]) + (z * a.mm[2][0]),
					(x * a.mm[0][1]) + (y * a.mm[1][1]) + (z * a.mm[2][1]),
					(x * a.mm[0][2]) + (y * a.mm[1][2]) + (z * a.mm[2][2]));
}
Vector3D Vector3D::operator*(const Matrix2D & a) {
	return Vector3D((x * a.mm[0][0]) + (y * a.mm[1][0]) + (z * a.mm[2][0]), 
					(x * a.mm[0][1]) + (y * a.mm[1][1]) + (z * a.mm[2][1]), 
					(x * a.mm[0][2]) + (y * a.mm[1][2]) + (z * a.mm[2][2]));
}
bool Vector3D::operator==(const Vector3D & rhs) const { return (x == rhs.x) && (y == rhs.y) && (z == rhs.z); }
bool Vector3D::operator!=(const Vector3D & rhs) const { return (x != rhs.x) || (y != rhs.y) || (z != rhs.z); }
bool Vector3D::operator<(const Vector3D & rhs) const { return (x < rhs.x && y < rhs.y && z < rhs.z) ? true : false; }
bool Vector3D::operator>(const Vector3D & rhs) const { return (x > rhs.x && y > rhs.y && z > rhs.z) ? true : false; }

Vector3D Vector3D::Cross(const Vector3D &a, const Vector3D &b) { return Vector3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.z); }

Vector3D Vector3D::minv(const Vector3D & a, const Vector3D & b) { return (a.x < b.x && a.y < b.y && a.z < b.z) ? a : b; }
Vector3D Vector3D::maxv(const Vector3D & a, const Vector3D & b) { return (a.x < b.x && a.y < b.y && a.z < b.z) ? b : a; }
Vector3D Vector3D::clampv(const Vector3D & a, const Vector3D & a_min, const Vector3D & a_max) { return minv(maxv(a, a_min), a_max); }
