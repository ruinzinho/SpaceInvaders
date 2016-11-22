#include "Shader.hpp"

#include <gl/glew.h>

#include "Log.hpp"


Shader::Shader(void) {
	id = 0;
}


Shader::Shader(const Shader &shader) {
	id = shader.id;
}


Shader &Shader::operator=(const Shader &shader) {
	id = shader.id;

	return *this;
}


Shader::~Shader(void) {
}


void Shader::Compile(const std::string &code) {
	const GLchar *data = code.c_str();

	glShaderSource(id, 1, &data, nullptr);
	glCompileShader(id);

	GLint status = GL_FALSE;
	GLint length = 0;

	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

	if (status == GL_FALSE) {
		GLchar *info = new GLchar[length];
		glGetShaderInfoLog(id, length, nullptr, info);
		Log::Error(info);
		delete[] info;
		exit(EXIT_FAILURE);
	}
}


void Shader::Delete(void) {
	glDeleteShader(id);
}


unsigned int Shader::Id(void) {
	return id;
}