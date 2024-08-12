#pragma once
#include "SpriteComponent.h"
#include <string>
#include <vector>

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(class Entity* owner, int drawOrder=100);
	~TileMapComponent();
	void setTileMap(std::string fileName);
	void setTileCol(int col) { mTilesCol = col; };
private:
	void draw(SDL_Renderer* renderer) override;
	std::vector<std::string> split(std::string& str, char delimiter);
	std::vector<std::vector<int>>mTileMap;
	int mTilesCol;
};
