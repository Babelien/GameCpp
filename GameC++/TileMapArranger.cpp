#include "TileMapArranger.h"
#include "Tile.h"
#include "Game.h"
#include "VertexArray.h"
#include "Texture.h"
#include <fstream>
#include <sstream>
#include <SDL/SDL.h>

using json = nlohmann::json;

TileMapArranger::TileMapArranger(Game* game)
	: mGame(game)
	, mTexture(nullptr)
	, mTextureWidth(64)
	, mTextureHeight(64)
	, mRhombusWidth(64)
	, mRhombusHeight(32)
	, colVec(Vec2(mRhombusWidth/2, -mRhombusHeight/2))
	, rowVec(Vec2(-mRhombusWidth/2, -mRhombusHeight/2))
{

}

TileMapArranger::~TileMapArranger()
{

}

void TileMapArranger::setTexture(Texture* texture)
{
	mTexture = texture;
}

Vec2 TileMapArranger::culcTilePos(int row, int col)
{
	return row * rowVec + col * colVec;
}

const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG = 0x20000000;
const unsigned ROTATED_HEXAGONAL_120_FLAG = 0x10000000;

void TileMapArranger::arrange()
{
	for (int layer = 0; layer < mTileMap["layers"].size(); ++layer)
	{
		for (int chunk = 0; chunk < mTileMap["layers"][layer]["chunks"].size(); ++chunk)
		{
			json curChunk = mTileMap["layers"][layer]["chunks"][chunk];
			std::vector<uint32_t>data = curChunk["data"].get<std::vector<uint32_t>>();
			int cx = curChunk["x"].get<int>();
			int cy = curChunk["y"].get<int>();
			int cwidth = curChunk["width"].get<int>();
			int cheight = curChunk["height"].get<int>();
			for (int row = 0; row < cheight; ++row)
			{
				for (int col = 0; col < cwidth; ++col)
				{
					int index = cwidth * row + col;
					if (data[index] <= 0)continue;
					//上位4bit(タイルの状態)を0にし代入
					uint32_t localTileID = data[index] & ~(FLIPPED_HORIZONTALLY_FLAG | 
						                                   FLIPPED_VERTICALLY_FLAG | 
						                                   FLIPPED_DIAGONALLY_FLAG | 
						                                   ROTATED_HEXAGONAL_120_FLAG);
					int x = row + cy;
					int y = col + cx;
					int drawOrder = x + y + 2 * layer;
					Tile* tile = new Tile(mGame, drawOrder);
					tile->getSprite()->setTexture(mTexture);
					tile->getSprite()->setTexWidth(mTextureWidth);
					tile->getSprite()->setTexHeight(mTextureHeight);
					uint32_t firstGID = 1; // タイルセットのオフセット
					tile->getSprite()->setSpriteVerts(createSpriteVerts(localTileID - firstGID));
					Vec2 pos = culcTilePos(x, y);
					tile->setPosition(pos);
				}
			}
		}
	}
}

void TileMapArranger::setTileMap(std::string fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs) SDL_Log("failed to find tile map file");
	mTileMap = json::parse(ifs);
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
