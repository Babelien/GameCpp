#include "game.h"

Game::Game() 
{
	window = nullptr;
	isRunning = true;
}

bool Game::initialize(const char* gameTitle)
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("SDLを初期化できません：%s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(
		gameTitle,
		100,
		100,
		1024,
		768,
		0
	);
	if (!window)
	{
		SDL_Log("ウィンドウの作成に失敗しました：%s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!renderer)
	{
		SDL_Log("レンダラの作成に失敗しました：%s", SDL_GetError());
		return false;
	}
}

void Game::shutdown()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void Game::runLoop()
{
	while (isRunning)
	{
		processInput();
		updateGame();
		generateOutput();
	}
}

void Game::updateGame()
{

}

void Game::processInput()
{
	SDL_Event event;


	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}
}

void Game::generateOutput()
{
	{}
}

