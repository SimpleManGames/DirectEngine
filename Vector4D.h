#ifndef _VECTOR4D_H
#define _VECTOR4D_H

#ifndef _VECTOR3D_H
#include "Vector3D.h"
#endif // _VECTOR3D_H


__declspec(align(32)) class Vector4D
{
public:
	union
	{
		Vector3D xyz;
		Vector3D rgb;
		Vector3D stp;
		float v[4];
		struct { float x, y, z, w; };
		struct { float r, g, b, a; };
		struct { float s, t, p, q; };
	};
public:
	Vector4D() 
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f) { }
	Vector4D(const Vector4D& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
	}
	Vector4D(double xPos, double yPos, double zPos, double wPos)
		: x((float)xPos)
		, y((float)yPos)
		, z((float)zPos)
		, w((float)wPos) { }
	
	~Vector4D();

	static Vector4D ZeroVector;
};

#endif // !_VECTOR4D_H