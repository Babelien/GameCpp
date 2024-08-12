#pragma once
#include <string>
#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();
	bool load(const std::string& vertName, const std::string& fragName);
	void setActive();
private:
	bool compileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
	bool isValidProgram();
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};
