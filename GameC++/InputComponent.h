#pragma once
#include "MoveComponent.h"

class InputComponent : public MoveComponent
{
public:
	InputComponent(class Entity* owner);
	void processInput(const uint8_t* keyState) override;
	void setForwardKey(int key) { mForwardKey = key; }
	void setBackKey(int key) { mBackKey = key; }
	void setClockwiseKey(int key) { mClockwiseKey = key; }
	void setCounterClockwiseKey(int key) { mCounterClockwiseKey = key; }
	void setMaxForwardSpeed(int speed) { mMaxForwardSpeed = speed; }
	void setMaxAngularSpeed(int speed) { mMaxAngularSpeed = speed; }
private:
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;
	int mForwardKey;
	int mBackKey;
	int mClockwiseKey;
	int mCounterClockwiseKey;
};
