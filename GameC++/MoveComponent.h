#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	MoveComponent(class Entity* owner, int updateOrder = 10);
	void update(float deltaTime) override;
	float getAngularSpeed() const { return mAngularSpeed; }
	float getForwardSpeed() const { return mForwardSpeed; }
	void setAngularSpeed(float speed) { mAngularSpeed = speed; }
	void setForwardSpeed(float speed) { mForwardSpeed = speed; }
private:
	float mAngularSpeed;
	float mForwardSpeed;
};
