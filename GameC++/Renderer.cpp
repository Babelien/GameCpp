#include "Renderer.h"
#define GLEW_STATIC
#include <GLEW/glew.h>
#include "SpriteComponent.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Shader.h"
#include "math.h"
#include <SDL/SDL.h>

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

bool Renderer::initialize(float screenWidth, float screenHeight, const char* gameTitle)
{
	mWindowWidth = screenWidth;
	mWindowHeight = screenHeight;
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("failed to init SDL : %s", SDL_GetError());
		return false;
	}

	// コアOpenGLプロファイルを使う
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// バージョン3.3を指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA各チャネル8ビットのカラーバッファを使う
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// ダブルバッファを有効にする
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// ハードウェアアクセラレーションを使う
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow(gameTitle, 100, 100, screenWidth, screenHeight, SDL_WINDOW_OPENGL);
	if (!mWindow)
	{
		SDL_Log("failed to create window : %s", SDL_GetError());
		return false;
	}

	mContext = SDL_GL_CreateContext(mWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("GLEWの初期化に失敗しました。");
		return false;
	}
	glGetError();

	if (!loadShaders())
	{
		SDL_Log("failed to load shader : %s", SDL_GetError());
		return false;
	}

	return true;
}

void Renderer::shutdown()
{
	unloadData();
	delete SpriteComponent::sDefSpriteVerts;
	mSpriteShader->unload();
	delete mSpriteShader;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Renderer::draw()
{
	// アルファブレンディング
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 画面クリア
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	mSpriteShader->setActive();
	for (auto sprite : mSprites)
	{
		sprite->draw(mSpriteShader);
	}

	SDL_GL_SwapWindow(mWindow);
}

bool Renderer::loadShaders()
{
	mSpriteShader = new Shader();
	if (!mSpriteShader->load("Shaders/Shader.vert", "Shaders/Shader.frag"))
	{
		return false;
	}
	mSpriteShader->setActive();
	Mat4 viewProj = Mat4::CreateSimpleViewProj(mWindowWidth, mWindowHeight);
	mSpriteShader->setMatrixUniform("uViewProj", viewProj);
	return true;
}

void Renderer::removeSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Renderer::addSprite(SpriteComponent* sprite)
{
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); iter++)
	{
		if (sprite->getDrawOrder() < (*iter)->getDrawOrder())
		{
			break;
		}
	}
	//イテレータの位置の前に挿入
	mSprites.insert(iter, sprite);
}

Texture* Renderer::getTexture(const std::string& filePath)
{
	Texture* tex = nullptr;
	auto iter = mTextures.find(filePath);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->load(filePath))
		{
			mTextures.emplace(filePath, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}

	return tex;
}

void Renderer::unloadData()
{
	for (auto m : mTextures)
	{
		m.second->unload();
		delete m.second;
	}

	mTextures.clear();
}
