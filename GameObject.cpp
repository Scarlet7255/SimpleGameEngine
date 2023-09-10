#include "GameObject.h"
#include "Component.h"
#include <algorithm>

GameObject::GameObject(std::string name)
{
	mState = GameObject::EActive;
	mName = name;
}

GameObject::~GameObject()
{
	mDeadComponents.clear();
	for (auto i : mNewComponents) {
		delete i;
	}
	mNewComponents.clear();
	for (auto i : mComponents) {
		delete i;
	}
	mComponents.clear();
}

void GameObject::Update(float deltaTime)
{
	if (mState != GameObject::EActive)
		return;
	UpdateComponents(deltaTime);
}

void GameObject::Wake()
{
	if(mState != GameObject::EDead)
		mState = GameObject::EActive;
}

void GameObject::Pause()
{
	if (mState != GameObject::EDead)
		mState = GameObject::EPaused;
}

void GameObject::Destroy()
{
	mState = GameObject::EDead;
}

void GameObject::AddComponent(Component* component)
{
	mNewComponents.push_back(component);
}

void GameObject::RemoveComponent(Component* component)
{
	auto it = mDeadComponents.find(component);
	
	if (it == mDeadComponents.end()) 
	{
		component->SetState(Component::Dead);
		mComponents.push_back(component);
	}
}


void GameObject::UpdateComponents(float deltaTime) 
{
	for (const auto i : mComponents)
	{
		if (i->GetState() == Component::Enable) 
		{
			i->Update(deltaTime);
		}
	}
	ClearDeadComponents();
	AddNewComponents();
}

void GameObject::ClearDeadComponents()
{
	for (auto it = mDeadComponents.begin(); it != mDeadComponents.end(); ++it)
	{
		for (auto i = mComponents.begin(); i != mComponents.end(); ++i)
		{
			if (*i == *it)
			{
				mComponents.erase(i);
				break;
			}
		}
		delete (*it);
	}
	mDeadComponents.clear();
}

void GameObject::AddNewComponents()
{
	for (const auto i : mNewComponents) 
	{
		mComponents.push_back(i);
	}
	mNewComponents.clear();
	sort(mComponents.begin(), mComponents.end(), [](Component* a, Component* b) {
		return a->GetUpdateOrder() < b->GetUpdateOrder();
		});
}