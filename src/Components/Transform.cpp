#include "Transform.h"

void Transform::SetPosition(float x, float y, float z)
{
	mDirty = true;
	mTranslation = {x,y,z};
}

void Transform::SetScale(float x, float y, float z)
{
	mDirty = true;
	mScale = {x,y,z};
}

void Transform::Rotate(float x, float y, float z, float w)
{
	mDirty = true;
	mRotation = {x,y,z,w};
}

Eigen::Matrix4f Transform::CreateScaleMatrix(Eigen::Vector3f scale)
{
	Eigen::Matrix4f res = Eigen::Matrix4f::Zero();
	res(0, 0) = scale[0];
	res(1, 1) = scale[1];
	res(2, 2) = scale[2];
	res(3, 3) = 1;
	return res;
}

Eigen::Matrix4f Transform::CreateRotationMatrix(Eigen::Vector4f rotation)
{
	float w = rotation[3];
	rotation[3] = 0;
	rotation = rotation.normalized();

	float x = rotation[0];
	float y = rotation[1];
	float z = rotation[2];

	Eigen::Matrix4f res = Eigen::Matrix4f::Zero();
	res(0, 0) = 1 - 2 * y * y - 2 * z * z;
	res(0, 1) = 2 * x * y - 2 * w * z;
	res(0, 2) = 2 * x * z + 2 * w * y;
	res(1, 0) = 2 * x * y + 2 * w * z;
	res(1, 1) = 1 - 2 * x * x - 2 * z * z;
	res(1, 2) = 2 * y * z - 2 * w * x;
	res(2, 0) = 2 * x * z - 2 * w * y;
	res(2, 1) = 2 * y * z - 2 * w * x;
	res(2, 2) = 1 - 2 * x * x - 2 * y * y;
	res(3, 3) = 1;
	return res;
}

Eigen::Matrix4f Transform::CreateTranslationMatrix(Eigen::Vector3f translation)
{
	Eigen::Matrix4f res = Eigen::Matrix4f::Zero();

	res(0,3) = translation[0];
	res(1, 3) = translation[1];
	res(2, 3) = translation[2];
	res(3, 3) = 1;
	return res;
}

void Transform::Update(float deltatime)
{
	UpdateTransfrom();
}

void Transform::UpdateTransfrom()
{
	if (!mDirty)
		return;
	mTransform = CreateTranslationMatrix(mTranslation)*CreateRotationMatrix(mRotation)*CreateScaleMatrix(mScale);
	mDirty = false;
}


