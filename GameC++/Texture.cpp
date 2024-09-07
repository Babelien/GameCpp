#include "Texture.h"
#include <SOIL/SOIL.h>
#include <GLEW/glew.h>
#include <SDL/SDL.h>

Texture::Texture()
	:mTextureID(0)
	,mWidth(0)
	,mHeight(0)
{

}

Texture::~Texture()
{

}

bool Texture::load(const std::string& filePath)
{
	int channels = 0;
	// テクスチャ読み込み
	unsigned char* image = SOIL_load_image(
		filePath.c_str(),
		&mWidth,
		&mHeight,
		&channels,
		SOIL_LOAD_AUTO
	);
	if (image == nullptr)
	{
		SDL_Log("failed to load texture image %s!：%s",filePath.c_str(), SOIL_last_result());
	}
	int format = GL_RGB;
	if (channels == 4)
	{
		format = GL_RGBA;
	}

	// OpenGLテクスチャオブジェクトの作成
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		format,
		mWidth,
		mHeight,
		0,
		format,
		GL_UNSIGNED_BYTE,
		image
	);

	// 画像データの解放
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;
}

void Texture::unload()
{
	glDeleteTextures(1, &mTextureID);
}

void Texture::setActive()
{
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}