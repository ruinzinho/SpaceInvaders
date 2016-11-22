#pragma once

#include <string>
#include <map>

#include "IProgram.hpp"
#include "ShaderProgram.hpp"

class ShaderFactory {
	std::map<std::string, ShaderProgram> shaderPrograms;

public:
	ShaderFactory(void);
	ShaderFactory(const ShaderFactory &shaderFactory);
	ShaderFactory &operator=(const ShaderFactory &shaderFactory);
	~ShaderFactory(void);

public:
	void Initialize(void);

public:
	IProgram &IluminationShader(void);

public:
	void Delete(void);

private:
	std::string ReadFromFile(const std::string &filename);
	ShaderProgram CreateShaderProgramFromFile(const std::string &vert, const std::string &frag);
};