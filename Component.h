#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

class Component
{
public:
	enum State 
	{
		Enable,
		Disable,
		Dead
	};

	Component(class GameObject* owner, int updateOrder = 100);
	virtual ~Component();

    virtual	void Update(float deltaTime);

	void SetState(State state) 
	{
		if (mState != Dead)
			mState = state;
	}

	int GetUpdateOrder() const {
		return mUpdateOrder;
	};

	State GetState() const {
		return mState;
	};

protected:
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void OnDestroy();

private:
	class GameObject* gameObject;
	int mUpdateOrder;
	State mState;
};

#endif // !COMPONENT_H