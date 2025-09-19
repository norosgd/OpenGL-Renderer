#pragma once
#include <string>

class Shader
{
public:
	unsigned int m_Id;

	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	void use();
};