#include "Asteroid.h"
#include "Game.h"
#include "Renderer.h"
#include "MoveComponent.h"
#include "Random.h"
#include "Texture.h"

Asteroid::Asteroid(Game* game)
	:Entity(game)
{
	Vec2 randPos = Random::GetVector(Vec2(-1024.f / 2, -768.f / 2), Vec2(1024.f/2, 768.f/2));
	setPosition(randPos);
	setRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent* sc = new SpriteComponent(this);
	sc->setTexture(game->getRenderer()->getTexture("Assets/Asteroid.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->setForwardSpeed(150.0f);
}