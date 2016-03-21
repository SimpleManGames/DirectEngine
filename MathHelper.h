#ifndef _MATHHELPER_H
#define _MATHHELPER_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "Vector2D.h"
#include "Vector3D.h"

static float toDegrees(float radians)
{
	return (float)(radians*(180.0f / M_PI));
	return 0.0f;
}

static float toRadians(float degrees)
{
	return (float)(degrees*(M_PI / 180.0f));
	return 0.0f;
}

static float round(float r)
{
	return (r > 0.0f) ? floor(r + 0.5f) : ceil(r - 0.5f);
}

template <typename T>
static T clamp(T min, T value, T max)
{
	if (value < min)
	{
		return min;
	}
	else if (value > max)
	{
		return max;
	}

	return value;
}

template <typename T>
static T minimum(T a, T b)
{
	return (a < b ? a : b);
}

template <typename T>
static T maximum(T a, T b)
{
	return (a > b ? a : b);
}

static float lerp(float start, float end, float t)
{
	return ((float)1 - t)*start + t*end;
}

static Vector2D lerp(Vector2D start, Vector2D end, float dt)
{
	float x, y;
	x = lerp(start[0], end[0], dt);
	y = lerp(start[1], end[1], dt);

	return Vector2D(x, y);
}

static Vector3D lerp(Vector3D start, Vector3D end, float dt)
{
	float x, y, z;
	x = lerp(start[0], end[0], dt);
	y = lerp(start[1], end[1], dt);
	z = lerp(start[1], end[1], dt);

	return Vector3D(x, y, z);
}

#endif