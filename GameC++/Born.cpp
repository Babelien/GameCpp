#include "Born.h"
#include "AnimSpriteComponent.h"

Born::Born(Game* game)
	:Entity(game)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*>anims{
		getGame()->getTexture("Assets/Character01.png"),
		getGame()->getTexture("Assets/Character02.png"),
		getGame()->getTexture("Assets/Character03.png"),
		getGame()->getTexture("Assets/Character04.png"),
		getGame()->getTexture("Assets/Character05.png"),
		getGame()->getTexture("Assets/Character06.png")
	};
	asc->setAnimTextures(anims);
	asc->setAnimFPS(10);
	addComponent(asc);
}

Born::~Born()
{

}