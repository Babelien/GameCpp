#pragma once
#include <SDL2/SDL.h>

class Game
{
public:
	Game();

	bool initialize(const char* gameTitle);
	void runLoop();
	void shutdown();

private:
	void processInput();
	void updateGame();
	void generateOutput();

	SDL_Window* window;
	bool isRunning;
	SDL_Renderer* renderer;
};