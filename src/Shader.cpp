#include <fstream>
#include <sstream>
#include <SDL.h>
#include "Shader.h"

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
	//compile vertex and fragment shaders
	if (CompileShader(vertName, GL_VERTEX_SHADER, mVertexShader) && CompileShader(fragName, GL_FRAGMENT_SHADER, mFragShader))
	{
		mShaderProgram = glCreateProgram();
		glAttachShader(mShaderProgram, mVertexShader);
		glAttachShader(mShaderProgram, mFragShader);
		glLinkProgram(mShaderProgram);

		if (!IsValidProgram()) 
		{
			return false;
		}
		return true;
	}


	return false;
}

void Shader::UnLoad()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragShader);
}

void Shader::Active()
{
	glUseProgram(mShaderProgram);
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
	// open file
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open()) 
	{
		// read all shader file text into a string
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();
		//create a shader of specific type
		outShader = glCreateShader(shaderType);

		// set the source characters and try to compile
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader)) 
		{
			SDL_Log("Failed to compile shader %s", fileName.c_str());
			return false;
		}
	}
	else 
	{
		SDL_Log("Shader file not found: %s", fileName.c_str());
		return false;
	}
	return true;
}

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;
	// query compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) 
	{
		char buffer[255];
		memset(buffer, 0, 255);//set buffer to all 0 
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n %s", buffer);
		return false;
	}
	return true;
}

bool Shader::IsValidProgram()
{
	GLint status;
	// query compile status
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[255];
		memset(buffer, 0, 255);//set buffer to all 0 
		SDL_Log("GLSL Compile Failed:\n %s", buffer);
		return false;
	}
	return true;
}
