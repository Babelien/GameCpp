#include "Component.h"
#include "Entity.h"

Component::Component(Entity* owner, int updateOrder)
	:mOwner(owner)
	,mUpdateOrder(updateOrder)
{
	owner->addComponent(this);
}

Component::~Component()
{
	mOwner->removeComponent(this);
}

void Component::update(float deltaTime)
{

}