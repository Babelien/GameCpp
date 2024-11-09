#include "Game.h"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"
#include "Renderer.h"
#include "Asteroid.h"
#include "Ship.h"
#include "TileMapArranger.h"

Game::Game()
	: mWindow(nullptr)
	, mContext(nullptr)
	, mIsRunning(true)
	, mFps(60)
{
	
}

bool Game::initialize(const char* gameTitle = "Game")
{
	mRenderer = new Renderer();
	mRenderer->initialize(mWindowWidth, mWindowHeight, gameTitle);

	loadData();

	return true;
}

void Game::shutdown()
{
	mRenderer->shutdown();
}

void Game::runLoop()
{
	while (mIsRunning)
	{
		processInput();
		updateGame();
		generateOutput();
	}
}

void Game::updateGame()
{
	// �t���[������
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + getIdealFrameTime()));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f; //�b

	if (0.05f < deltaTime)
	{
		deltaTime = 0.05f;
	}

	// �S�A�N�^�[�̍X�V
	mUpdatingEntities = true;
	for (auto actor : mEntities)
	{
		actor->update(deltaTime);
	}
	mUpdatingEntities = false;

	// �҂��ɂȂ��Ă����A�N�^�[�̒ǉ�
	for (auto pending : mPendingEntities)
	{
		pending->computeWorldTransform();
		mEntities.emplace_back(pending);
	}
	mPendingEntities.clear();

	// ���񂾃A�N�^�[���ꎞ�z��ɒǉ�
	std::vector<Entity*>pDeadActors;
	for (auto actor : mEntities)
	{
		if (actor->getState() == Entity::eDead)
		{
			pDeadActors.emplace_back(actor);
		}
	}

	// ���񂾃A�N�^�[������
	for (auto actor : pDeadActors)
	{
		delete actor;
	}

	mTicksCount = SDL_GetTicks();
}

void Game::processInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingEntities = true;
	for (auto actor : mEntities)
	{
		actor->processInput(state);
	}
	mUpdatingEntities = false;
}

void Game::generateOutput()
{
	mRenderer->draw();

}

void Game::addEntity(Entity* entity)
{
	if (!mUpdatingEntities)
	{
		mEntities.emplace_back(entity);
	}
	else
	{
		mPendingEntities.emplace_back(entity);
	}
}

void Game::removeEntity(Entity* entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);
	if (iter != mEntities.end())
	{
		std::iter_swap(iter, mEntities.end() - 1);
		mEntities.pop_back();
	};

	iter = std::find(mPendingEntities.begin(), mPendingEntities.end(), entity);
	if (iter != mPendingEntities.end())
	{
		std::iter_swap(iter, mPendingEntities.end() - 1);
		mPendingEntities.pop_back();
	}
}

void Game::loadData() 
{
	// CreateMap
	TileMapArranger* ta = new TileMapArranger(this);
	ta->setTexture(getRenderer()->getTexture("Assets/TileMap/Tiles.png"));
	ta->setTileMap("Assets/TileMap/Map.tmj");
	ta->arrange();
}

void Game::unloadData()
{
	while (!mEntities.empty())
	{
		delete mEntities.back();
	}

	mRenderer->unloadData();
}

float Game::getIdealFrameTime()
{
	return 1000.0f / mFps;
}