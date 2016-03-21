#pragma once

#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix3.h"

class Quaternion
{
public:
	Quaternion(void)
	{
		value[0] = 1;
		value[1] = 0;
		value[2] = 0;
		value[3] = 0;
	}

	Quaternion(float w, float x, float y, float z)
	{
		value[0] = w;
		value[1] = x;
		value[2] = y;
		value[3] = z;
	}

	Quaternion(float w, Vector3D &v)
	{
		value[0] = w;
		value[1] = v[0];
		value[2] = v[1];
		value[3] = v[2];
	}

	~Quaternion(void)
	{
	}

	Quaternion(const Vector3D& axis, float angle)
	{
		fromAxisAngle(axis, angle);
	}

	float w() const { return value[0]; }
	float& w()		{ return value[0]; }
	float x() const { return value[1]; }
	float& x()		{ return value[1]; }
	float y() const { return value[2]; }
	float& y()		{ return value[2]; }
	float z() const { return value[3]; }
	float& z()		{ return value[3]; }

	Quaternion& operator= (const Quaternion& q)
	{
		value[0] = q[0];
		value[1] = q[1];
		value[2] = q[2];
		value[3] = q[3];
		return *this;
	}

	bool operator== (const Quaternion& q)
	{
		if (value[0] == q[0] && value[1] == q[1] && value[2] == q[2] && value[3] == q[3]) { return true; }
		else { return false; }
	}

	bool operator!= (const Quaternion& q)
	{
		if (value[0] != q[0] || value[1] != q[1] || value[2] != q[2] || value[3] != q[3]) { return true; }
		else { return false; }
	}

	bool operator< (const Quaternion& q)
	{
		if (value[0] < q[0] && value[1] < q[1] && value[2] < q[2] && value[3] < q[3]) { return true; }
		else { return false; }
	}

	bool operator<= (const Quaternion& q)
	{
		if (value[0] <= q[0] && value[1] <= q[1] && value[2] <= q[2] && value[3] <= q[3]) { return true; }
		else { return false; }
	}

	bool operator> (const Quaternion& q)
	{
		if (value[0] > q[0] && value[1] > q[1] && value[2] > q[2] && value[3] > q[3]) { return true; }
		else { return false; }
	}

	bool operator>= (const Quaternion& q)
	{
		if (value[0] >= q[0] && value[1] >= q[1] && value[2] >= q[2] && value[3] >= q[3]) { return true; }
		else { return false; }
	}

	Quaternion operator+ (const Quaternion& q)
	{
		Quaternion result;

		result[0] = value[0] + q[0];
		result[1] = value[1] + q[1];
		result[2] = value[2] + q[2];
		result[3] = value[3] + q[3];

		return result;
	}

	Quaternion operator- (const Quaternion& q)
	{
		Quaternion result;

		result[0] = value[0] - q[0];
		result[1] = value[1] - q[1];
		result[2] = value[2] - q[2];
		result[3] = value[3] - q[3];

		return result;
	}

	Quaternion operator* (const Quaternion& q)
	{
		Quaternion result;

		float w = value[0] * q[0] - value[1] * q[1] - value[2] * q[2] - value[3] * q[3];
		float x = value[0] * q[1] + value[1] * q[0] - value[2] * q[3] + value[3] * q[2];
		float y = value[0] * q[2] + value[1] * q[3] + value[2] * q[0] - value[3] * q[1];
		float z = value[0] * q[3] - value[1] * q[2] + value[2] * q[1] + value[3] * q[0];

		return Quaternion(w, x, y, z);
	}

	Quaternion operator* (float scalar)
	{
		float w = value[0] * scalar;
		float x = value[1] * scalar;
		float y = value[2] * scalar;
		float z = value[3] * scalar;

		return Quaternion(w, x, y, z);
	}

	Quaternion operator/ (float scalar)
	{
		float invScalar = ((float)1) / scalar;

		float w = value[0] * invScalar;
		float x = value[1] * invScalar;
		float y = value[2] * invScalar;
		float z = value[3] * invScalar;

		return Quaternion(w, x, y, z);
	}

	Quaternion operator- () const
	{
		return Quaternion(-value[0], -value[1], -value[2], -value[3]);
	}

	Quaternion& operator+= (const Quaternion& q)
	{
		for (int i = 0; i < 4; ++i)
		{
			value[i] += q[i];
		}
		return *this;
	}

	Quaternion& operator-= (const Quaternion& q)
	{
		for (int i = 0; i < 4; ++i)
		{
			value[i] -= q[i];
		}
		return *this;
	}

	Quaternion& operator*= (float scalar)
	{
		for (int i = 0; i < 4; ++i)
		{
			value[i] *= scalar;
		}
		return *this;
	}

	Quaternion& operator/= (float scalar)
	{
		float invScalar = ((float)1) / scalar;
		for (int i = 0; i < 4; ++i)
		{
			value[i] *= invScalar;
		}
		return *this;
	}

	static Quaternion fromRotationMatrix(Matrix3& rot)
	{
		float w = std::sqrt((1 + rot.getValue(0) + rot.getValue(4) + rot.getValue(8))) / 2.0f;
		float w4 = 4 * w;
		float x = (rot.getValue(7) - rot.getValue(5)) / w4;
		float y = (rot.getValue(2) - rot.getValue(6)) / w4;
		float z = (rot.getValue(3) - rot.getValue(1)) / w4;

		if (std::fabs(w4) < 0.0000001f)
		{
			return Quaternion(1, 0, 0, 0);
		}

		return Quaternion(w, x, y, z);
	}

	void toRotationMatrix(Matrix3& rot)
	{
		rot[0] = (this->w() * this->w()) + (this->x() * this->x()) - (this->y() * this->y()) - (this->z() * this->z());
		rot[1] = 2 * (this->x() * this->y()) - 2 * (this->w() * this->z());
		rot[2] = 2 * (this->x() * this->z()) + 2 * (this->w() * this->y());

		rot[3] = 2 * (this->x() * this->y()) + 2 * (this->w() * this->z());
		rot[4] = (this->w() * this->w()) - (this->x() * this->x()) + (this->y() * this->y()) - (this->z() * this->z());
		rot[5] = 2 * (this->y() * this->z()) - 2 * (this->w() * this->x());

		rot[6] = 2 * (this->x() * this->z()) - 2 * (this->w() * this->y());
		rot[7] = 2 * (this->y() * this->z()) + 2 * (this->w() * this->x());
		rot[8] = (this->w() * this->w()) - (this->x() * this->x()) - (this->y() * this->y()) + (this->z() * this->z());
	}

	void fromAxisAngle(const Vector3D& axis, float angle)
	{
		float halfAngle = angle / 2;

		Vector3D noramlizeAxis = axis;
		noramlizeAxis = noramlizeAxis.Normalize();

		value[0] = std::cos(halfAngle);
		value[1] = noramlizeAxis[0] * std::sin(halfAngle);
		value[2] = noramlizeAxis[1] * std::sin(halfAngle);
		value[3] = noramlizeAxis[2] * std::sin(halfAngle);
	}

	void toAxisAngle(Vector3D& axis, float& angle)
	{
		float sqrLength = value[1] * value[1] + value[2] * value[2] + value[3] * value[3];

		if (sqrLength > 1e-06f)
		{
			angle = ((float)2)*std::acos(value[0]);
			float invLength = 1 / std::sqrt(sqrLength);;
			axis[0] = value[1] * invLength;
			axis[1] = value[2] * invLength;
			axis[2] = value[3] * invLength;
		}
		else
		{
			angle = (float)0;
			axis[0] = (float)1;
			axis[1] = (float)0;
			axis[2] = (float)0;
		}
	}

	float length()
	{
		return std::sqrt(value[0] * value[0] + value[1] * value[1] +
			value[2] * value[2] + value[3] * value[3]);
	}

	float squaredLength()
	{
		return value[0] * value[0] + value[1] * value[1] +
			value[2] * value[2] + value[3] * value[3];
	}

	float dot(const Quaternion& q)
	{
		return value[0] * q.value[0] + value[1] * q.value[1] +
			value[2] * q.value[2] + value[3] * q.value[3];
	}

	void normalize()
	{
		float len = length();
		if (std::fabs(len) < 0.0000001f)
		{
			// divide by zero 
			value[0] = 1;
			value[1] = 0;
			value[2] = 0;
			value[3] = 0;
		}
		else
		{
			value[0] /= len;
			value[1] /= len;
			value[2] /= len;
			value[3] /= len;
		}
	}

	Quaternion inverse()
	{
		Quaternion inverse;

		float norm = squaredLength();
		if (norm > (float)0)
		{
			float invNorm = ((float)1) / norm;
			inverse[0] = value[0] * invNorm;
			inverse[1] = -value[1] * invNorm;
			inverse[2] = -value[2] * invNorm;
			inverse[3] = -value[3] * invNorm;
		}
		else
		{
			for (int i = 0; i < 4; ++i)
			{
				inverse[i] = (float)0;
			}
		}

		return inverse;
	}

	Quaternion conjugate()
	{
		return Quaternion(value[0], -value[1], -value[2], -value[3]);
	}

	Vector3D rotate(Vector3D& vec)
	{
		Matrix3 rot;
		this->toRotationMatrix(rot);
		return rot * vec;
	}

	Quaternion lerp(Quaternion &q1, Quaternion &q2, float t)
	{
		Quaternion q = (q1*(1.0f - t) + q2*t);
		q.normalize();
		return q;
	}

	Quaternion& slerp(float t, Quaternion& p, Quaternion& q)
	{
		float cs = p.dot(q);
		float angle = std::acos(cs);

		if (std::fabs(angle) >= 1e-06f)
		{
			float sn = std::sin(angle);
			float invSn = ((float)1) / sn;
			float tAngle = t*angle;
			float coeff0 = std::sin(angle - tAngle)*invSn;
			float coeff1 = std::sin(tAngle)*invSn;

			value[0] = coeff0*p[0] + coeff1*q[0];
			value[1] = coeff0*p[1] + coeff1*q[1];
			value[2] = coeff0*p[2] + coeff1*q[2];
			value[3] = coeff0*p[3] + coeff1*q[3];
		}
		else
		{
			value[0] = p[0];
			value[1] = p[1];
			value[2] = p[2];
			value[3] = p[3];
		}

		return *this;
	}

	float& operator [](unsigned int i)
	{
		return value[i];
	}

	float operator [](unsigned int i) const
	{
		return value[i];
	}

private:
	float value[4];

};

