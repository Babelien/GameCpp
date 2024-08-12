#include "CircleComponent.h"
#include "Entity.h"

CircleComponent::CircleComponent(Entity* owner)
	:Component(owner)
{

}

float CircleComponent::getRadius() const
{
	return mOwner->getScale() * mRadius;
}

const Vec2& CircleComponent::getCenter() const
{
	return mOwner->getPosition();
}

bool intersect(const CircleComponent &a, const CircleComponent &b)
{
	float center_sq = (b.getCenter() - a.getCenter()).LengthSq();
	float radius_sq = Math::Sqrt(b.getRadius() + a.getRadius());
	return center_sq <= radius_sq;
}