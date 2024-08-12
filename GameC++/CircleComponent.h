#pragma once
#include "Component.h"
#include "Math.h"

class CircleComponent : public Component
{
public:
	CircleComponent(class Entity* owner);

	void setRadius(float radius) { mRadius = radius; }
	float getRadius() const;
	const Vec2& getCenter() const;
private:
	float mRadius;
};

bool intersect(const CircleComponent &a, const CircleComponent &b);