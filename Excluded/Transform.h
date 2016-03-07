#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "Vector2D.h"
#include "Matrix3.h"

#include <list>

class Transform
{
	Transform *e_parent;
	std::list<Transform*> e_children;
	Vector2D position, scale;
	float angle;
	// Matrix3 local; Updates whenever a setter is used

public:
	Transform();
	~Transform();

	//Matrix4 version to use with drawing.
	Matrix3 getGlobalTransform() const;

	void setParent(Transform *);
	void setPosition(const Vector2D &);
	void setScale(const Vector2D &);
	void setAngle(float);

	Vector2D getPosition() const;
	Vector2D getScale() const;
	float   getAngle() const;

	Vector2D getRight()     const;
	Vector2D getUp()        const;
};

#endif