#pragma once
#include <string>
#include <GLEW/glew.h>

class Shader
{
public:
	Shader();
	~Shader();
	bool load(const std::string& vertPath, const std::string& fragPath);
	void unload();
	void setActive();
	void setMatrixUniform(const char* name, const class Mat4& matrix);
private:
	bool compileShader(const std::string& filePath, GLenum shaderType, GLuint& outShader);
	bool isCompiled(GLuint shader);
	bool isValidProgram();
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};
