#pragma once
#include "../Component.h"
class Renderer :
    public Component
{
public:
    Renderer(class GameObject* owner, int updateOrder = 100);
    virtual void Draw(class Shader* shader);

protected:
    void OnEnable() override;
    void OnDisable() override;
};

