#include "Ship.h"
#include "Game.h"
#include "Renderer.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Texture.h"

Ship::Ship(Game* game)
	:Entity(game)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->setTexture(game->getRenderer()->getTexture("Assets/Ship.png"));

	InputComponent* ic = new InputComponent(this);
	ic->setForwardKey(SDL_SCANCODE_W);
	ic->setBackKey(SDL_SCANCODE_S);
	ic->setClockwiseKey(SDL_SCANCODE_A);
	ic->setCounterClockwiseKey(SDL_SCANCODE_D);
	ic->setMaxForwardSpeed(300.0f);
	ic->setMaxAngularSpeed(Math::TwoPi);
}