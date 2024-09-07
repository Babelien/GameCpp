#pragma once
#include <vector>
#include <unordered_map>
#include <SDL/SDL.h>
#include <string>

class Renderer
{
public:
	Renderer();
	~Renderer();
	bool initialize(float screenWidth, float screenHeight, const char* gameTitle);
	void shutdown();
	void unloadData();
	void draw();
	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	class Texture* getTexture(const std::string& filePath);
private:
	bool loadShaders();
	
	std::unordered_map<std::string, class Texture*> mTextures;
	std::vector<class SpriteComponent*> mSprites;
	class SDL_Window* mWindow;
	float mWindowWidth, mWindowHeight;
	SDL_GLContext mContext;
	class Shader* mSpriteShader;
};
