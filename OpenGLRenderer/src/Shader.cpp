#include "Shader.h"
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	std::ifstream vertexShaderFile(vertexShaderPath);
	std::ifstream fragmentShaderFile(fragmentShaderPath);

	std::stringstream vertexShaderStream, fragmentShaderStream;

	vertexShaderStream << vertexShaderFile.rdbuf();
	fragmentShaderStream << fragmentShaderFile.rdbuf();

	std::string vertexShaderCode = vertexShaderStream.str();
	std::string fragmentShaderCode = fragmentShaderStream.str();

	const char* vShaderCode = vertexShaderCode.c_str();
	const char* fShaderCode = fragmentShaderCode.c_str();

    unsigned int vertexShader, fragmentShader;
    int compileStatus;
    char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    //Shader debug
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    m_Id = glCreateProgram();
    glAttachShader(m_Id, vertexShader);
    glAttachShader(m_Id, fragmentShader);
    glLinkProgram(m_Id);

    //program debugging
    glGetProgramiv(m_Id, GL_LINK_STATUS, &compileStatus);
    if (!compileStatus)
    {
        glGetProgramInfoLog(m_Id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use()
{
    glUseProgram(m_Id);
}
