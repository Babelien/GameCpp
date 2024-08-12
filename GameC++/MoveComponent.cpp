#include "MoveComponent.h"
#include "Entity.h"
#include "Math.h"
MoveComponent::MoveComponent(Entity* owner, int updateOrder)
	:Component(owner, updateOrder)
	,mAngularSpeed(0.0f)
	,mForwardSpeed(0.0f)
{
	
}

void MoveComponent::update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		float rot = mOwner->getRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->setRotation(rot);
	}

	if (!Math::NearZero(mForwardSpeed))
	{
		Vec2 pos = mOwner->getPosition();
		pos += mOwner->getForward() * mForwardSpeed * deltaTime;
		mOwner->setPosition(pos);
	}
}