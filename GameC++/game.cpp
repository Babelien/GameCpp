#include "Game.h"
#include <GL/glew.h>
#include "Born.h"
#include "Tile.h"
#include "Asteroid.h"
#include "Ship.h"

Game::Game()
	:mWindow(nullptr)
	, mIsRunning(true)
	, mFps(60)
{
	
}

bool Game::initialize(const char* gameTitle = "Game")
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("failed to init SDL : %s", SDL_GetError());
		return false;
	}

	// �R�AOpenGL�v���t�@�C�����g��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// �o�[�W����3.3���w��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA�e�`���l��8�r�b�g�̃J���[�o�b�t�@���g��
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// �_�u���o�b�t�@��L���ɂ���
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// �n�[�h�E�F�A�A�N�Z�����[�V�������g��
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow(gameTitle, 100, 100, mWindowWidth, mWindowHeight, SDL_WINDOW_OPENGL);
	if (!mWindow)
	{
		SDL_Log("failed to create window : %s", SDL_GetError());
		return false;
	}

	mContext = SDL_GL_CreateContext(mWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("GLEW�̏������Ɏ��s���܂����B");
		return false;
	}
	glGetError();

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("failed to init image : %s", SDL_GetError());
		return false;
	}

	loadData();

	return true;
}

void Game::shutdown()
{
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
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
	//=============================================================================
	//                               YOUR CODE START
	//=============================================================================

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

	//=============================================================================
	//                                YOUR CODE END
	//=============================================================================
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
	// ��ʃN���A
	glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	for (auto sprite : mSprites)
	{
		sprite->draw(mRenderer);
	}

	SDL_GL_SwapWindow(mWindow);

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

void Game::loadData() {
	const int numAsteroid = 20;

	for (int i = 0; i < numAsteroid; i++)
	{
		new Asteroid(this);
	}

	Entity* actor = new Ship(this);
	addEntity(actor);
}

float Game::getIdealFrameTime()
{
	return 1000.0f / mFps;
}

SDL_Texture* Game::loadTexture(const std::string& fileName)
{
	SDL_Surface* surface = IMG_Load(fileName.c_str());
	if (!surface)
	{
		SDL_Log("failed to load img %s", fileName.c_str());
		return nullptr;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
	{
		SDL_Log("failed to convert surface to texture for %s", fileName.c_str());
		return nullptr;
	}
	return texture;
}

SDL_Texture* Game::getTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = loadTexture(fileName);
		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::addSprite(SpriteComponent* sprite)
{
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); iter++)
	{
		if (sprite->getDrawOrder() < (*iter)->getDrawOrder())
		{
			break;
		}
	}
	//�C�e���[�^�̈ʒu�̑O�ɑ}��
	mSprites.insert(iter, sprite);
}

void Game::removeSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}