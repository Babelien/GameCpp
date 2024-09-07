#pragma once
#include "Component.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Entity* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void draw(class Shader* shader);
	virtual void setTexture(class Texture* texture);
	void setSpriteVerts(class VertexArray* spriteVerts) { mSpriteVerts = spriteVerts; }
	void setTexWidth(int width) { mTexWidth = width; }
	void setTexHeight(int height) { mTexHeight = height; }
	void createDefSpriteVerts();
	int getDrawOrder() const { return mDrawOrder; };
	int getTexWidth() const { return mTexWidth; };
	int getTexHeight() const { return mTexHeight; };
	class VertexArray* getSpriteVerts() const { return mSpriteVerts; }

	static class VertexArray* sDefSpriteVerts;
protected:
	class VertexArray* mSpriteVerts;
	class Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
};
