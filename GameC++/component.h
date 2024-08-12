#pragma once
#include <cstdint>
class Component
{
public:
	Component(class Entity* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void update(float deltaTime);
	virtual void processInput(const uint8_t* keyState) {}
	int getUpdateOrder() const { return mUpdateOrder; }

protected:
	class Entity* mOwner;
	int mUpdateOrder;
};
