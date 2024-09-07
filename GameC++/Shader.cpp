#include "Shader.h"
#include <fstream>
# include <sstream>
#include "math.h"
#include <SDL/SDL.h>
# include <iostream>;

Shader::Shader()
{

}

Shader::~Shader()
{

}

bool Shader::compileShader(const std::string& filePath, GLenum shaderType, GLuint& outShader)
{
	std::ifstream shaderFile(filePath);
	if (shaderFile.is_open())
	{
		// すべてのテキストを１つの文字列に読み込む
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		// 指定されたタイプのシェーダを作成
		outShader = glCreateShader(shaderType);
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!isCompiled(outShader))
		{
			SDL_Log("failed to compile %s ", filePath.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file %s is not found", filePath.c_str());
		return false;
	}
	return true;
}

bool Shader::load(const std::string& vertPath, const std::string& fragPath)
{
	// 頂点シェーダとフラグメントシェーダをコンパイルする
	if (!compileShader(vertPath, GL_VERTEX_SHADER, mVertexShader) || !compileShader(fragPath, GL_FRAGMENT_SHADER, mFragShader))
	{
		return false;
	}

	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);

	if (!isValidProgram())
	{
		return false;
	}

	return true;
}

void Shader::setActive()
{
	glUseProgram(mShaderProgram);
}

void Shader::unload()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragShader);
}

void Shader::setMatrixUniform(const char* name, const Mat4& matrix)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, name);
	glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}

bool Shader::isValidProgram()
{
	GLint status;
	//コンパイル状態を問い合わせる
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("Failed to create Program：\n%s", buffer);
		return false;
	}
	return true;
}

bool Shader::isCompiled(GLuint shader)
{
	GLint status;
	//コンパイル状態を問い合わせる
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("Failed to Compile GLSL：\n%s", buffer);
		return false;
	}
	return true;
}