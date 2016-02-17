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
	Vector4D();
	~Vector4D();
};

#endif // !_VECTOR4D_H