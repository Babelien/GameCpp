#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_main.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include "Math.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"

class Game
{
public:
	Game();

	bool initialize(const char* gameTitle);
	void runLoop();
	void shutdown();
	void addEntity(Entity *entity);
	void removeEntity(Entity *entity);
	void removeSprite(class SpriteComponent* sprite);
	SDL_Texture* loadTexture(const std::string &fileName);
	float getIdealFrameTime();
	SDL_Texture* getTexture(const std::string& fileName);
	void setFps(float fps) { mFps = fps; };
	void addSprite(SpriteComponent* sprite);

private:
	void processInput();
	void updateGame();
	void generateOutput();
	void loadData();

	int mWindowWidth = 1024;
	int mWindowHeight = 768;
	SDL_Window* mWindow;
	SDL_GLContext mContext;
	bool mIsRunning;
	Uint32 mTicksCount;
	int mFps;
	std::vector<Entity *> mEntities;
	std::vector<Entity*> mPendingEntities;
	std::vector<SpriteComponent*>mSprites;
	bool mUpdatingEntities;
	std::unordered_map<std::string, SDL_Texture*> mTextures;
};