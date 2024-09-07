#include "TileMapArranger.h"
#include "Tile.h"
#include "Game.h"
#include "VertexArray.h"
#include "Texture.h"
#include <fstream>
#include <sstream>
#include <SDL/SDL.h>

TileMapArranger::TileMapArranger(Game* game)
	: mGame(game)
	, mTexture(nullptr)
	, mTextureWidth(64)
	, mTextureHeight(64)
	, mRhombusWidth(64)
	, mRhombusHeight(32)
{

}

TileMapArranger::~TileMapArranger()
{

}

void TileMapArranger::setTexture(Texture* texture)
{
	mTexture = texture;
}

void TileMapArranger::arrange()
{
	int layer = 0;
	for (int row = 0; row < mTileMap.size(); ++row)
	{
		for (int col = 0; col < mTileMap[row].size(); ++col)
		{
			if (mTileMap[row][col] == -1)continue;
			int drawOrder = row + col;
			Tile* tile = new Tile(mGame, drawOrder);
			tile->setMapPos(Vec3(col, row, layer));
			tile->getSprite()->setTexture(mTexture);
			tile->getSprite()->setTexWidth(mTextureWidth);
			tile->getSprite()->setTexHeight(mTextureHeight);
			tile->getSprite()->setSpriteVerts(createSpriteVerts(mTileMap[row][col]));
			float x = (col- row) * static_cast<float>(mRhombusWidth) / 2;
			float y = -(row + col) * static_cast<float>(mRhombusHeight) / 2;
			tile->setPosition(Vec2(x,y));
		}
	}
}

void TileMapArranger::setTileMap(std::string fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs) SDL_Log("failed to find tile map file");
	std::string line;
	while (std::getline(ifs, line))
	{
		std::vector<std::string>str = split(line, ',');
		std::vector<int>ivec;
		for (auto& s : str)ivec.emplace_back(std::stoi(s));
		mTileMap.push_back(ivec);
	}
}

std::vector<std::string> TileMapArranger::split(std::string& str, char delimiter)
{
	std::vector<std::string>strvec;
	std::istringstream iss(str);
	std::string field;
	while (std::getline(iss, field, delimiter))strvec.emplace_back(field);
	return strvec;
}

VertexArray* TileMapArranger::createSpriteVerts(int tileNumber)
{
	int tilesCol = getTexture()->getWidth() / mTextureWidth;
	int tilesRow = getTexture()->getHeight() / mTextureHeight;
	float nWidth = 1.0f / tilesCol;
	float nHeight = 1.0f / tilesRow;
	float topLeftX = tileNumber % tilesCol * nWidth;
	float topLeftY = tileNumber / tilesCol * nHeight;
	float vertices[] = {
		-0.5f,  0.5f, 0.f, topLeftX, topLeftY,                    // top left
		 0.5f,  0.5f, 0.f, topLeftX + nWidth, topLeftY,           // top right
		 0.5f, -0.5f, 0.f, topLeftX + nWidth, topLeftY + nHeight, // bottom right
		-0.5f, -0.5f, 0.f, topLeftX, topLeftY + nHeight           // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	return new VertexArray(vertices, 4, indices, 6);
}
