#pragma once

#include "Entity.h"


class Tile : public Entity
{
public:
	Tile(class Game* game, int drawOrder);
	class SpriteComponent* getSprite() const { return mSprite; }
	void setMapPos(Vec3 mapPos) { mMapPos = mapPos; }
	class Vec3 getMapPos() const { return mMapPos; }
private:
	class SpriteComponent* mSprite;
	Vec3 mMapPos;
};
