#include "SpriteComponent.h"
#include <GLEW/glew.h>
#include "Component.h"
#include "Entity.h"
#include "Game.h"
#include "Renderer.h"
#include "Math.h"
#include "Texture.h"
#include "Shader.h"
#include "VertexArray.h"

VertexArray* SpriteComponent::sDefSpriteVerts = nullptr;

SpriteComponent::SpriteComponent(Entity* owner, int drawOrder)
	: Component(owner)
	,mDrawOrder(drawOrder)
	,mTexture(nullptr)
	,mTexHeight(0)
	,mTexWidth(0)
	,mSpriteVerts(nullptr)
{
	if(sDefSpriteVerts == nullptr)createDefSpriteVerts();
	Renderer* renderer = owner->getGame()->getRenderer();
	renderer->addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	Renderer* renderer = mOwner->getGame()->getRenderer();
	renderer->removeSprite(this);
}

void SpriteComponent::draw(Shader* shader)
{
	mSpriteVerts != nullptr ? mSpriteVerts->setActive() : SpriteComponent::sDefSpriteVerts->setActive();
	
	if (mTexture)
	{
		Mat4 scaleMat = Mat4::CreateScale(
			static_cast<int>(mTexWidth),
			static_cast<int>(mTexHeight),
			1.0f);
		Mat4 world = scaleMat * mOwner->getWorldTransform();
		shader->setMatrixUniform("uWorldTransform", world);
		mTexture->setActive();
		glDrawElements(
			GL_TRIANGLES,
			6,
			GL_UNSIGNED_INT,
			nullptr
		);
	}
}

void SpriteComponent::setTexture(Texture* texture)
{
	mTexture = texture;
	mTexWidth = texture->getWidth();
	mTexHeight = texture->getHeight();
}

void SpriteComponent::createDefSpriteVerts()
{
	float vertices[] = {
		-0.5f,  0.5f, 0.f, 0.f, 0.f, // top left
		 0.5f,  0.5f, 0.f, 1.f, 0.f, // top right
		 0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
		-0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	sDefSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}