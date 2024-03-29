#pragma once
#include <vector>
#include "math.h"

class Actor
{
public:
	enum State
	{
		active,
		paused,
		dead
	};
	Actor(class Game *pGame);
	virtual ~Actor();
	void addComponent(class Component *pComponent);
	void removeComponent(class Component *pComponent);
	void update(float deltaTime);
	void updateComponents(float deltaTime);
	virtual void updateActor(float deltaTime); // 派生クラスの独自アップデート

	void setState(State state) { this->state = state; };
	State getState() { return state; };
private:
	State state;
	Vec2 position;
	float scale;
	float rotation;
	std::vector<class Component*>pComponents;
	class Game* pGame;
};
