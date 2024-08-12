#pragma once
#include "SpriteComponent.h"
#include <vector>
class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Entity* owner, int drawOrder = 100);
	//~AnimSpriteComponent();
	void update(float deltaTime) override;
	void setAnimTextures(const std::vector<SDL_Texture*>& textures);
	float getAnimFPS() const { return mAnimFPS; };
	void setAnimFPS(float fps) { mAnimFPS = fps; };

private:
	std::vector<SDL_Texture*>mAnimTextures;
	float mCurrFrame;
	float mAnimFPS;
};
