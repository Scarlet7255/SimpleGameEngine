#include "Component.h"

Component::Component(GameObject* owner, int updateOrder)
{
	mState = Component::Enable;
}

Component::~Component()
{
	OnDisable();
	OnDestroy();
}

void Component::Update(float deltaTime)
{
}

void Component::OnEnable()
{
}

void Component::OnDisable()
{
}

void Component::OnDestroy()
{
}
