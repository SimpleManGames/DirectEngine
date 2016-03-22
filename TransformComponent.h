#ifndef _TRANSFORM_COMPONENT_H
#define _TRANSFORM_COMPONENT_H

#include "Component.h"
#include "MathHelper.h"
#include "Vector3D.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Quaternion.h"

class GameObject;
class TransformComponent
	: public Component
{
public:
	TransformComponent()
	{
		this->Awake();
	}

	Quaternion m_rotation;
	Vector3D m_up;
	Vector3D m_right;
	Vector3D m_direction;
	Vector3D m_position;

	Matrix3 m_scale;

	Matrix4 m_localMatrix;
	Matrix4 m_worldMatrix;
	Matrix4 m_mv;
	Matrix4 m_mvp;

	virtual void Destory();
	virtual void Awake();
	virtual void Start();
	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();

	TransformComponent* setRotation(Quaternion q);
	Quaternion getRotation();
	
	TransformComponent* rotate(Vector3D axis, float angle);

	TransformComponent* rotateX(float angle);
	TransformComponent* rotateY(float angle);
	TransformComponent* rotateZ(float angle);

	Vector3D getRight();
	Vector3D getUp();
	Vector3D getDirection();
	
	Vector3D& getPosition();
	Vector3D getWorldPosition();
	
	TransformComponent* setPosition(Vector3D position);
	TransformComponent* translate(float translate);
	TransformComponent* translate(Vector3D translate);
	TransformComponent* translate(float x, float y, float z);

	Matrix3 getScale();
	float getScaleX();
	float getScaleY();
	float getScaleZ();

	TransformComponent* setScale(float scale);
	TransformComponent* setScale(Vector3D scale);
	TransformComponent* setScale(float x, float y, float z);

	TransformComponent* scale(float scale);
	TransformComponent* scale(Vector3D scale);
	TransformComponent* scale(float x, float y, float z);

	Matrix4 getLocalMatrix();
	Matrix4 getWorldMatrix();
	Matrix4 getMVMatrix();
	Matrix4 getMVPMatrix();
};

#endif