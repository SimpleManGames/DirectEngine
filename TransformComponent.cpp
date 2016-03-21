#include "TransformComponent.h"
#include "GameObject.h"

void TransformComponent::Destory() { }

void TransformComponent::Awake()
{
	this->m_up = Vector3D(0, 1, 0);
	this->m_right = Vector3D(1, 0, 0);
	this->m_direction = Vector3D(0, 0, 1);

	this->m_rotation = Quaternion(1, 0, 0, 0);
	
	this->m_position = Vector3D(0, 0, 0);

	this->m_scale = Matrix3();
}
void TransformComponent::Start()
{
	this->m_localMatrix = Matrix4::toMatrix4(this->m_rotation, this->m_position, this->m_scale);

	this->m_up = Vector3D(this->m_localMatrix[1], this->m_localMatrix[5], this->m_localMatrix[9]);
	this->m_right = Vector3D(this->m_localMatrix[0], this->m_localMatrix[4], this->m_localMatrix[8]);
	this->m_direction = Vector3D(this->m_localMatrix[2], this->m_localMatrix[6], this->m_localMatrix[10]);

	this->m_worldMatrix = this->m_localMatrix;

	if (this->m_gameObject->m_parent != NULL)
	{
		this->m_worldMatrix = this->m_gameObject->m_parent->m_transform->m_worldMatrix * this->m_worldMatrix;
	}
}
void TransformComponent::FixedUpdate()
{
	this->m_localMatrix = Matrix4::toMatrix4(this->m_rotation, this->m_position, this->m_scale);

	this->m_up = Vector3D(this->m_localMatrix[1], this->m_localMatrix[5], this->m_localMatrix[9]);
	this->m_right = Vector3D(this->m_localMatrix[0], this->m_localMatrix[4], this->m_localMatrix[8]);
	this->m_direction = Vector3D(this->m_localMatrix[2], this->m_localMatrix[6], this->m_localMatrix[10]);

	this->m_worldMatrix = this->m_localMatrix;

	if (this->m_gameObject->m_parent != NULL)
	{
		this->m_worldMatrix = this->m_gameObject->m_parent->m_transform->m_worldMatrix * this->m_worldMatrix;
	}
}
void TransformComponent::Update()
{
	this->m_localMatrix = Matrix4::toMatrix4(this->m_rotation, this->m_position, this->m_scale);

	this->m_up = Vector3D(this->m_localMatrix[1], this->m_localMatrix[5], this->m_localMatrix[9]);
	this->m_right = Vector3D(this->m_localMatrix[0], this->m_localMatrix[4], this->m_localMatrix[8]);
	this->m_direction = Vector3D(this->m_localMatrix[2], this->m_localMatrix[6], this->m_localMatrix[10]);

	this->m_worldMatrix = this->m_localMatrix;

	if (this->m_gameObject->m_parent != NULL)
	{
		this->m_worldMatrix = this->m_gameObject->m_parent->m_transform->m_worldMatrix * this->m_worldMatrix;
	}
}
void TransformComponent::LateUpdate()
{
	this->m_localMatrix = Matrix4::toMatrix4(this->m_rotation, this->m_position, this->m_scale);

	this->m_up = Vector3D(this->m_localMatrix[1], this->m_localMatrix[5], this->m_localMatrix[9]);
	this->m_right = Vector3D(this->m_localMatrix[0], this->m_localMatrix[4], this->m_localMatrix[8]);
	this->m_direction = Vector3D(this->m_localMatrix[2], this->m_localMatrix[6], this->m_localMatrix[10]);

	this->m_worldMatrix = this->m_localMatrix;

	if (this->m_gameObject->m_parent != NULL)
	{
		this->m_worldMatrix = this->m_gameObject->m_parent->m_transform->m_worldMatrix * this->m_worldMatrix;
	}
}

TransformComponent * TransformComponent::setRotation(Quaternion q)
{
	this->m_rotation = q;
	return this;
}
Quaternion TransformComponent::getRotation() { return this->m_rotation; }

TransformComponent * TransformComponent::rotate(Vector3D axis, float angle)
{
	Quaternion quat;
	quat.fromAxisAngle(axis, toRadians(angle));
	this->m_rotation = this->m_rotation * quat;

	return this;
}
TransformComponent * TransformComponent::rotateX(float angle)
{
	Quaternion quat;
	quat.fromAxisAngle(this->m_right, toRadians(angle));
	this->m_rotation = this->m_rotation * quat;
	return this;
}
TransformComponent * TransformComponent::rotateY(float angle)
{
	Quaternion quat;
	quat.fromAxisAngle(this->m_up, toRadians(angle));
	this->m_rotation = this->m_rotation * quat;
	return this;
}
TransformComponent * TransformComponent::rotateZ(float angle)
{
	Quaternion quat;
	quat.fromAxisAngle(this->m_direction, toRadians(angle));
	this->m_rotation = this->m_rotation * quat;
	return this;
}

Vector3D TransformComponent::getRight() { return this->m_right; }
Vector3D TransformComponent::getUp() { return this->m_up; }
Vector3D TransformComponent::getDirection() { return this->m_direction; }

Vector3D TransformComponent::getPosition() { return this->m_position; }
Vector3D TransformComponent::getWorldPosition()
{
	if (this->m_gameObject->m_parent != NULL)
		return this->m_gameObject->m_parent->m_transform->getWorldPosition() + this->m_position;

	return this->m_position;
}
TransformComponent * TransformComponent::setPosition(Vector3D position)
{
	this->m_position = position;

	return this;
}

TransformComponent * TransformComponent::translate(float translate)
{
	this->m_position += translate;

	return this;
}
TransformComponent * TransformComponent::translate(Vector3D translate)
{
	this->m_position += translate;

	return this;
}
TransformComponent * TransformComponent::translate(float x, float y, float z)
{
	this->m_position += { x, y, z };

	return this;
}

Matrix3 TransformComponent::getScale()
{
	return m_scale;
}
float TransformComponent::getScaleX()
{
	return m_scale[0];
}
float TransformComponent::getScaleY()
{
	return m_scale[4];
}
float TransformComponent::getScaleZ()
{
	return m_scale[8];
}

TransformComponent * TransformComponent::setScale(float scale)
{
	m_scale[0] = scale;
	m_scale[4] = scale;
	m_scale[8] = scale;

	return this;
}
TransformComponent * TransformComponent::setScale(Vector3D scale)
{
	m_scale[0] = scale[0];
	m_scale[4] = scale[1];
	m_scale[8] = scale[2];

	return this;
}
TransformComponent * TransformComponent::setScale(float x, float y, float z)
{
	m_scale[0] = x;
	m_scale[4] = y;
	m_scale[8] = z;

	return this;
}

TransformComponent * TransformComponent::scale(float scale)
{
	m_scale[0] += scale;
	m_scale[4] += scale;
	m_scale[8] += scale;

	return this;
}
TransformComponent * TransformComponent::scale(Vector3D scale)
{
	m_scale[0] += scale[0];
	m_scale[4] += scale[1];
	m_scale[8] += scale[2];

	return this;
}
TransformComponent * TransformComponent::scale(float x, float y, float z)
{
	m_scale[0] += x;
	m_scale[4] += y;
	m_scale[8] += z;

	return this;
}

Matrix4 TransformComponent::getLocalMatrix()
{
	return this->m_localMatrix;
}

Matrix4 TransformComponent::getWorldMatrix()
{
	return this->m_worldMatrix;
}

Matrix4 TransformComponent::getMVMatrix()
{
	return this->m_mv;
}

Matrix4 TransformComponent::getMVPMatrix()
{
	return this->m_mvp;
}
