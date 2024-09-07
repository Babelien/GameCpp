#pragma once
#include <SDL/SDL.h>
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
	float getIdealFrameTime();
	void setFps(float fps) { mFps = fps; };
	class Renderer* getRenderer() const { return mRenderer; }
private:
	void processInput();
	void updateGame();
	void generateOutput();
	void loadData();
	void unloadData();
	bool loadShaders();
	void createSpriteVerts();

	int mWindowWidth = 1024;
	int mWindowHeight = 768;
	SDL_Window* mWindow;
	SDL_GLContext mContext;
	class Renderer* mRenderer;
	bool mIsRunning;
	Uint32 mTicksCount;
	int mFps;
	std::vector<Entity *> mEntities;
	std::vector<Entity*> mPendingEntities;
	std::vector<SpriteComponent*>mSprites;
	bool mUpdatingEntities;
	std::unordered_map<std::string, class Texture*> mTextures;
	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;
};