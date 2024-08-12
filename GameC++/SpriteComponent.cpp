#include "SpriteComponent.h"
#include "Component.h"
#include "Entity.h"
#include "Game.h"
#include "Math.h"

SpriteComponent::SpriteComponent(Entity* owner, int drawOrder)
	: Component(owner)
	,mDrawOrder(drawOrder)
	,mTexture(nullptr)
	,mTexHeight(0)
	,mTexWidth(0)
{
	owner->getGame()->addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->getGame()->removeSprite(this);
}

void SpriteComponent::draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;
		// 幅と高さを所持アクターのスケールで拡縮する
		r.w = static_cast<int>(mTexWidth * mOwner->getScale());
		r.h = static_cast<int>(mTexHeight * mOwner->getScale());
		// 矩形の中心を所持アクターに合わせる
		r.x = static_cast<int>(mOwner->getPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->getPosition().y - r.h / 2);
		//描画する
		SDL_RenderCopyEx(
			renderer,
			mTexture,
			nullptr,
			&r,
			-Math::ToDegrees(mOwner->getRotation()),
			nullptr,
			SDL_FLIP_NONE
		);
	}
}

void SpriteComponent::setTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight); //幅と高さを取得
}