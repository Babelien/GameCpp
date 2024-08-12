#pragma once
#include <vector>
#include "Math.h"

class Entity
{
public:
	enum State
	{
		eActive,
		ePaused,
		eDead
	};
	Entity(class Game *game);
	virtual ~Entity();
	void addComponent(class Component *component);
	void removeComponent(class Component *component);
	void update(float deltaTime);
	void updateComponents(float deltaTime);
	virtual void updateActor(float deltaTime); // 派生クラス独自のアップデート
	void processInput(const uint8_t* keyState);
	virtual void actorInput(const uint8_t* keyState);
	void setState(State state) { mState = state; };
	void setPosition(const Vec2 &vec2) { mPosition = vec2; };
	void setRotation(float rotation) { mRotation = rotation; }
	State getState() const { return mState; };
	float getScale() const { return mScale; };
	const Vec2& getPosition() const { return mPosition; };
	float getRotation() const { return mRotation; };
	Vec2 getForward() const { return Vec2(Math::Cos(mRotation), -Math::Sin(mRotation)); }
	class Game* getGame() const { return mGame; }
private:
	State mState;
	Vec2 mPosition;
	float mScale;
	float mRotation;
	std::vector<class Component*>mComponents;
	class Game* mGame;
};
