#include "Tile.h"
#include "Game.h"
#include "Texture.h"
#include "Renderer.h"
#include "SpriteComponent.h"

Tile::Tile(Game* game, int drawOrder)
	:Entity(game)
{
	mSprite = new SpriteComponent(this, drawOrder);
}