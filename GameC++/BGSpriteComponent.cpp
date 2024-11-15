#include "BGSpriteComponent.h"
#include "Entity.h"
#include "Shader.h"
#include "Texture.h"
#include <SDL/SDL.h>

BGSpriteComponent::BGSpriteComponent(class Entity* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
{

}

void BGSpriteComponent::setBGTextures(const std::vector<Texture*>& textures)
{
	for (int i = 0; i < textures.size(); i++)
	{
		BGTexture tmp;
		tmp.mTexture = textures[i];
		tmp.mOffset.x = i * mScreenSize.x;
		tmp.mOffset.y = 0;
		mBGTextures.emplace_back(tmp);
	}
}

void BGSpriteComponent::draw(Shader* shader)
{
	for (auto& bg : mBGTextures)
	{
		SDL_Rect r;
		r.w = mScreenSize.x;
		r.h = mScreenSize.y;
		r.x = static_cast<int>(mOwner->getPosition().x - r.w / 2 + bg.mOffset.x);
		r.y = static_cast<int>(mOwner->getPosition().y - r.h / 2 + bg.mOffset.y);

		//SDL_RenderCopy(renderer, bg.mTexture, nullptr, &r);
	}
}

void BGSpriteComponent::update(float deltaTime)
{
	SpriteComponent::update(deltaTime);
	for (auto& bg : mBGTextures)
	{
		bg.mOffset.x = mScrollSpeed * deltaTime;
		//完全に画面の外に出たとき
		if (bg.mOffset.x < -mScreenSize.x)
		{
			bg.mOffset.x = ( mBGTextures.size() - 1)* mScreenSize.x - 1;
		}
	}
}