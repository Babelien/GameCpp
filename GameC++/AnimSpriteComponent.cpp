#include "AnimSpriteComponent.h"
#include "Entity.h"
#include "Texture.h"
#include <vector>

AnimSpriteComponent::AnimSpriteComponent(Entity* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mAnimFPS(24.0f)
	, mCurrFrame(0)
{

}

void AnimSpriteComponent::setAnimTextures(const std::vector<Texture*>& textures)
{
	mAnimTextures = textures;
	setTexture(textures[0]);
	mCurrFrame = 0.0f;
}

void AnimSpriteComponent::update(float deltaTime)
{
	SpriteComponent::update(deltaTime);
	if (0 < mAnimTextures.size())
	{
		mCurrFrame += mAnimFPS * deltaTime;

		while (mAnimTextures.size() <= mCurrFrame)
		{
			mCurrFrame -= mAnimTextures.size();
		}

		setTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}