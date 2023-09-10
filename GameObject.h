#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <vector>
#include <unordered_set>
#include <string>

class GameObject
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	GameObject(std::string name= "");

	virtual ~GameObject();

	void Update(float deltaTime);
	void Destroy();
	void Wake();
	void Pause();

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	State GetState() const {
	 	return mState;
	};

private:

	void UpdateComponents(float deltaTime);
	void ClearDeadComponents();
	void AddNewComponents();

	State mState;
	std::string mName;

	std::vector<class Component*> mComponents;
	std::vector<class Component*> mNewComponents;
	std::unordered_set<class Component*> mDeadComponents;
};
#endif // !GAMEOBJECT_H


