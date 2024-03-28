#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "math.h"
#include "actor.h"

class Game
{
public:
	Game();

	bool initialize(const char* gameTitle);
	void runLoop();
	void shutdown();
	void setFps();
	void addActor(Actor *pActor);
	void removeActor(Actor *pActor);

private:
	void processInput();
	void updateGame();
	void generateOutput();
	float getIdealFrameTime();

	int windowWidth = 1024;
	int windowHeight = 768;
	SDL_Window* window;
	bool isRunning;
	SDL_Renderer* renderer;
	Uint32 ticksCount;
	int fps;
	std::vector<Actor *> pActors;
	std::vector<Actor*> pPendingActors;
	bool updatingActors;

	Vec2 paddlePos;
	Vec2 ballPos;
	Vec2 ballVel;
	const int thickness = 15;
	const int paddleScale = 100;
	int paddleDir;
};