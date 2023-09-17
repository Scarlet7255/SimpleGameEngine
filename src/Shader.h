#pragma once
#ifndef SHADER_H
#define SHADER_H

#include<string>
#include<glew.h>

class Shader
{
public:
	Shader();
	~Shader();

	// load vert and frag shader with given name and complie
	bool Load(const std::string& vertName, const std::string& fragName);
	void UnLoad();
	void Active();

private:
	bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
	bool IsCompiled(GLuint shader);
	// test whether vertex/fragment programs link
	bool IsValidProgram();
	// store shader object ids
	GLuint mVertexShader;
	GLuint mFragShader;
	GLuint mShaderProgram;
};
#endif // !SHADER_H


