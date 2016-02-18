#include "Vector3D.h"

Vector3D Vector3D::ZeroVector() { return Vector3D(0.0f, 0.0f, 0.0f); }

double Vector3D::Length() const { return sqrtf((float)x * (float)x + (float)y * (float)y + (float)z * (float)z); }
double Vector3D::Distance(const Vector3D & vec) const
{
	return sqrtf(((float)vec.x - (float)x)*((float)vec.x - (float)x) + ((float)vec.y - (float)y)*((float)vec.y - (float)y) + ((float)vec.z - (float)z)*((float)vec.z - (float)z));
}
double Vector3D::Dot(const Vector3D & vec) const { return (x * vec.x + y * vec.y + z * vec.z); }
Vector3D & Vector3D::Normalize()
{
	double xxyyzz = x * x + y * y + z * z;
	double invLength = 1.0 / sqrtf((float)xxyyzz);
	x *= (float)invLength;
	y *= (float)invLength;
	z *= (float)invLength;
	return *this;
}
float Vector3D::Magnitude() { return sqrtf(x * x + y * y + z * z); }

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
bool Vector3D::operator==(const Vector3D & rhs) const { return (x == rhs.x) && (y == rhs.y) && (z == rhs.z); }
bool Vector3D::operator!=(const Vector3D & rhs) const { return (x != rhs.x) || (y != rhs.y) || (z != rhs.z); }
bool Vector3D::operator<(const Vector3D & rhs) const
{
	if (x < rhs.x) return true;
	if (y < rhs.y) return true;
	if (z < rhs.z) return true;
	return false;
}

bool Vector3D::operator>(const Vector3D & rhs) const
{
	if (x > rhs.x) return true;
	if (y > rhs.y) return true;
	if (z > rhs.z) return true;
	return false;
}

Vector3D Vector3D::Cross(const Vector3D &a, const Vector3D &b) { return Vector3D(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.z); }

Vector3D Vector3D::min(const Vector3D & a, const Vector3D & b) { return a < b ? a : b; }

Vector3D Vector3D::max(const Vector3D & a, const Vector3D & b) { return a > b ? a : b; }

Vector3D Vector3D::clamp(const Vector3D & a, const Vector3D & a_min, const Vector3D & a_max) { return max(min(a_min, a_max), a_max); }
