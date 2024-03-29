#include "game.h"

Game::Game() 
{
	window = nullptr;
	isRunning = true;
	fps = 60;
	ballPos = { static_cast<float>(windowWidth / 2), static_cast<float>(windowHeight / 2) };
	paddlePos = { static_cast<float>(thickness / 2), static_cast<float>(windowHeight / 2) };
	ballVel = { -200.0f, 235.0f };
}

bool Game::initialize(const char* gameTitle)
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("failed to init SDL : %s", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow(gameTitle, 100, 100, windowWidth, windowHeight, 0);
	if (!window)
	{
		SDL_Log("failed to create window : %s", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
	{
		SDL_Log("failed to create renderer : %s", SDL_GetError());
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("failed to init image : %s", SDL_GetError());
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
	// フレーム制限
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + getIdealFrameTime()));
	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f; //秒

	if (0.05f < deltaTime)
	{
		deltaTime = 0.05f;
	}
	//=============================================================================
	//                               YOUR CODE START
	//=============================================================================

	// 全アクターの更新
	updatingActors = true;
	for (auto actor : pActors)
	{
		actor->update(deltaTime);
	}
	updatingActors = false;

	// 待ちになっていたアクターの追加
	for (auto pending : pPendingActors)
	{
		pActors.emplace_back(pending);
	}
	pPendingActors.clear();

	// 死んだアクターを一時配列に追加
	std::vector<Actor*>pDeadActors;
	for (auto actor : pActors)
	{
		if (actor->getState() == Actor::dead)
		{
			pDeadActors.emplace_back(actor);
		}
	}

	// 死んだアクターを消す
	for (auto actor : pDeadActors)
	{
		delete actor;
	}

	//=============================================================================
	//                                YOUR CODE END
	//=============================================================================
	ticksCount = SDL_GetTicks();
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

	paddleDir = 0;
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}
	if (state[SDL_SCANCODE_UP])
	{
		paddleDir -= 1;
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		paddleDir += 1;
	}
}

void Game::generateOutput()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	int wallCount = 3;
	SDL_Rect* walls = new SDL_Rect[wallCount];
	walls[0] = { 0, 0, windowWidth, thickness };
	walls[1] = { 0, windowHeight - thickness, windowWidth, thickness };
	walls[2] = { windowWidth - thickness, 0,thickness, windowHeight };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i < wallCount; i++)
	{
		SDL_RenderFillRect(renderer, &walls[i]);
	}

	SDL_Rect ball = { (ballPos.x - thickness / 2), (ballPos.y - thickness / 2) ,thickness, thickness};
	SDL_RenderFillRect(renderer, &ball);

	SDL_Rect paddle = { paddlePos.x - thickness / 2, paddlePos.y - paddleScale / 2, thickness, paddleScale };
	SDL_RenderFillRect(renderer, &paddle);

	SDL_RenderPresent(renderer);
}

void Game::addActor(Actor* pActor)
{
	if (!updatingActors)
	{
		pActors.emplace_back(pActor);
	}
	else
	{
		pPendingActors.emplace_back(pActor);
	}
}

void Game::removeActor(Actor* pActor)
{
	auto iter = std::find(pActors.begin(), pActors.end(), pActor);
	if (iter != pActors.end())
	{
		std::iter_swap(iter, pActors.end() - 1);
		pActors.pop_back();
	};

	iter = std::find(pPendingActors.begin(), pPendingActors.end(), pActor);
	if (iter != pPendingActors.end())
	{
		std::iter_swap(iter, pPendingActors.end() - 1);
		pPendingActors.pop_back();
	}
}

float Game::getIdealFrameTime()
{
	return 1000.0f / fps;
}

