#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "math.h"

class TileMapArranger
{
public:
	TileMapArranger(class Game* game);
	~TileMapArranger();
	void arrange();
	void setTexture(class Texture* texture);
	void setTileMap(std::string fileName);
	void setTextureWidth(float width) { mTextureWidth = width; }
	void setTextureHeight(float height) { mTextureHeight = height; }
	class Texture* getTexture() const { return mTexture; }
	Vec2 culcTilePos(int row, int col);
private:
	class VertexArray* createSpriteVerts(int tileNumber);
	class Game* mGame;
	std::vector<std::string> split(std::string& str, char delimiter);
	nlohmann::json mTileMap;
	class Texture* mTexture;
	float mRhombusWidth;
	float mRhombusHeight;
	float mTextureWidth;
	float mTextureHeight;
	Vec2 colVec, rowVec;
};
