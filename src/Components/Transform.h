#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../Component.h"
#include "Eigen/Core"
#include <vector>
class Transform :
    public Component
{

public:
    void SetPosition(float x, float y, float z);
    void SetScale(float x, float y, float z);
    void Rotate(float x, float y, float z, float w);

    const Eigen::Matrix4f WorldTransform() { return mTransform; };

    static Eigen::Matrix4f CreateScaleMatrix(Eigen::Vector3f scale);
    static Eigen::Matrix4f CreateRotationMatrix(Eigen::Vector4f rotation);
    static Eigen::Matrix4f CreateTranslationMatrix(Eigen::Vector3f translation);

    void Update(float deltatime) override;
private:
    Eigen::Matrix4f mTransform = Eigen::Matrix4f::Identity(4, 4);
    Eigen::Vector3f mTranslation = {0,0,0};
    Eigen::Vector4f mRotation = {0,1,0,1};
    Eigen::Vector3f mScale = {1,1,1};
    bool mDirty = false;

    void UpdateTransfrom();
};

#endif // !TRANSFORM
