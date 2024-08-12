#include "TileMapComponent.h"
#include "Entity.h"
#include <fstream>
#include <sstream>

TileMapComponent::TileMapComponent(Entity* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mTilesCol(8)
{

}

TileMapComponent::~TileMapComponent()
{

}

void TileMapComponent::draw(SDL_Renderer* renderer)
{
	if (!mTexture)
	{
		SDL_Log("did not set texture!");
		return;
	}

	int tileWidth = mTexWidth / mTilesCol;
	int tileHeight = tileWidth;

	for (int i = 0; i < mTileMap.size(); i++)
	{
		for (int j = 0; j < mTileMap[i].size(); j++)
		{
			if (0 <= mTileMap[i][j])
			{
				SDL_Rect sr;
				sr.w = tileWidth;
				sr.h = tileHeight;
				sr.x = tileWidth * (mTileMap[i][j]%mTilesCol);
				sr.y = tileHeight * mTileMap[i][j] / mTilesCol;
				SDL_Rect dr;
				// 幅と高さを所持アクターのスケールで拡縮する
				dr.w = static_cast<int>(tileWidth * mOwner->getScale());
				dr.h = static_cast<int>(tileHeight * mOwner->getScale());
				// 矩形の中心を所持アクターに合わせる
				dr.x = static_cast<int>(mOwner->getPosition().x - dr.w / 2 + tileWidth * j);
				dr.y = static_cast<int>(mOwner->getPosition().y - dr.h / 2 + tileHeight * i);
				//描画する
				SDL_RenderCopyEx(
					renderer,
					mTexture,
					&sr,
					&dr,
					Math::ToDegrees(mOwner->getRotation()),
					nullptr,
					SDL_FLIP_NONE
				);
			}
		}
	}
	
}

void TileMapComponent::setTileMap(std::string fileName)
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

std::vector<std::string> TileMapComponent::split(std::string& str, char delimiter)
{
	std::vector<std::string>strvec;
	std::istringstream iss(str);
	std::string field;
	while (std::getline(iss, field, delimiter))strvec.emplace_back(field);
	return strvec;
}
