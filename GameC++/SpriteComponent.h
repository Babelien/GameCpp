#pragma once
#include "Component.h"
#include <SDL/SDL.h>

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Entity* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void draw(SDL_Renderer* renderer);
	virtual void setTexture(SDL_Texture* texture);
	int getDrawOrder() const { return mDrawOrder; };
	int getTexWidth() const { return mTexWidth; };
	int getTexHeight() const { return mTexHeight; };

protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};
