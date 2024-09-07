#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <vector>
class BGSpriteComponent : SpriteComponent
{
public:
	BGSpriteComponent(class Entity* owner, int drawOrder = 10);
	void update(float deltaTime) override;
	void draw(class Shader* shader) override;
	void setBGTextures(const std::vector<class Texture*>& textures);
	void setScreenSize(const Vec2& size) { mScreenSize = size; };
	void setScrollSpeed(float speed) { mScrollSpeed = speed; };
	float getScrollSpeed() const { return mScrollSpeed; };
private:
	struct BGTexture
	{
		class Texture* mTexture;
		Vec2 mOffset;
	};

	std::vector<BGTexture> mBGTextures;
	Vec2 mScreenSize;
	float mScrollSpeed;
};
