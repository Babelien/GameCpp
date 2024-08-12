#include "Tile.h"
#include "Game.h"
#include "TileMapComponent.h"

Tile::Tile(Game* game)
	:Entity(game)
{
	TileMapComponent* tmc = new TileMapComponent(this);
	tmc->setTexture(getGame()->getTexture("Assets/Tiles.png"));
	tmc->setTileMap("Assets/MapLayer1.csv");
	addComponent(tmc);
}