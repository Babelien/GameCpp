#include "Asteroid.h"
#include "Game.h"
#include "MoveComponent.h"
#include "Random.h"

Asteroid::Asteroid(Game* game)
	:Entity(game)
{
	Vec2 randPos = Random::GetVector(Vec2::Zero, Vec2(1024.0f, 768.0f));
	setPosition(randPos);
	setRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent* sc = new SpriteComponent(this);
	sc->setTexture(game->getTexture("Assets/Asteroid.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->setForwardSpeed(150.0f);
}