#include "Transform.h"
#include "Vector2D.h"

Transform::Transform()
	: e_parent(nullptr)
	, scale({ 1,1 })
	, position({ 0,0 })
	, angle(0) { }
Transform::~Transform()
{
	auto t = e_children;
	for each(Transform *child in t)
		child->setParent(e_parent);

	setParent(nullptr);
}
void Transform::setParent(Transform *a_parent)
{
	// If we have a parent, we need to be set free!
	if (e_parent)
		e_parent->e_children.remove(this);

	// If the new parent isn't null, then adopt us!
	if (a_parent)
		a_parent->e_children.push_front(this);

	// Then set the parent
	e_parent = a_parent;
}

Matrix3 Transform::getGlobalTransform() const
{
	return
		(e_parent ? e_parent->getGlobalTransform()
			: Matrix3::CreateIdentityMatrix())
			* Matrix3::CreateTranslationMatrix(position)
			* Matrix3::CreateScalingMatrix(scale)
			* Matrix3::CreateRotationMatrix(angle);
}

void Transform::setPosition(const Vector2D &a_position) { position = a_position; }
void Transform::setScale(const Vector2D &a_scale) { scale = a_scale; }
void Transform::setAngle(float a_angle) { angle = a_angle; }
Vector2D Transform::getPosition() const { return position; }
Vector2D Transform::getScale() const { return scale; }
float Transform::getAngle() const { return angle; }
Vector2D Transform::getRight() const { return Vector2D::fromAngle(angle); }
Vector2D Transform::getUp() const { return Vector2D::Perp(Vector2D::fromAngle(angle)); }