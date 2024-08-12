#include "Entity.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Entity::Entity(Game* game)
	:mGame(game)
	, mState(eActive)
	, mPosition(Vec2::Zero)
	, mScale(1.0f)
	, mRotation(0.0f)
{
	mGame->addEntity(this);
}

Entity::~Entity()
{
	mGame->removeEntity(this);
	while (mComponents.size() != 0)
	{
		delete mComponents.back();
	}
}

void Entity::addComponent(Component* component)
{
	int order = component->getUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); iter++)
	{
		if (order < (*iter)->getUpdateOrder()) break;
	}
	mComponents.insert(iter, component);
}

void Entity::removeComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

void ::Entity::update(float deltaTime)
{
	if (mState == eActive)
	{
		updateComponents(deltaTime);
		updateActor(deltaTime);
	}
}

void Entity::updateComponents(float deltaTime)
{
	for (auto* c : mComponents) c->update(deltaTime);
}

void Entity::processInput(const uint8_t* keyState)
{
	if (mState == eActive)
	{
		for (auto comp : mComponents)
		{
			comp->processInput(keyState);
		}
	}
}



void Entity::updateActor(float deltaTime) {}
void Entity::actorInput(const uint8_t* keyState) {}