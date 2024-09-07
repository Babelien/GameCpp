#include "Born.h"
#include "AnimSpriteComponent.h"
#include "Texture.h"
#include "Renderer.h"

Born::Born(Game* game)
	:Entity(game)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<Texture*>anims{
		getGame()->getRenderer()->getTexture("Assets/Character01.png"),
		getGame()->getRenderer()->getTexture("Assets/Character02.png"),
		getGame()->getRenderer()->getTexture("Assets/Character03.png"),
		getGame()->getRenderer()->getTexture("Assets/Character04.png"),
		getGame()->getRenderer()->getTexture("Assets/Character05.png"),
		getGame()->getRenderer()->getTexture("Assets/Character06.png")
	};
	asc->setAnimTextures(anims);
	asc->setAnimFPS(10);
	addComponent(asc);
}

Born::~Born()
{

}