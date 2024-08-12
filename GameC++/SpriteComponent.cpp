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
		// ���ƍ����������A�N�^�[�̃X�P�[���Ŋg�k����
		r.w = static_cast<int>(mTexWidth * mOwner->getScale());
		r.h = static_cast<int>(mTexHeight * mOwner->getScale());
		// ��`�̒��S�������A�N�^�[�ɍ��킹��
		r.x = static_cast<int>(mOwner->getPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->getPosition().y - r.h / 2);
		//�`�悷��
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
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight); //���ƍ������擾
}