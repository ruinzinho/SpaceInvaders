#include "ShaderProgram.hpp"

#include <gl/glew.h>

#include "Log.hpp"


ShaderProgram::ShaderProgram(void) {
	id = 0;
}


ShaderProgram::ShaderProgram(const ShaderProgram &shaderProgram) {
	id = shaderProgram.id;
}


ShaderProgram &ShaderProgram::operator=(const ShaderProgram &shaderProgram) {
	id = shaderProgram.id;

	return *this;
}


ShaderProgram::~ShaderProgram(void) {
}


void ShaderProgram::Create(void) {
	id = glCreateProgram();
}


void ShaderProgram::AttachShader(Shader &shader) {
	glAttachShader(id, shader.Id());
}


void ShaderProgram::BindAttribLocation(unsigned int index, const std::string &name) {
	glBindAttribLocation(id, index, name.c_str());
}


void ShaderProgram::Link(void) {
	GLint status = GL_FALSE;
	GLint length = 0;

	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &status);
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

	if (status == GL_FALSE) {
		GLchar *info = new GLchar[length];
		glGetProgramInfoLog(id, length, nullptr, info);
		Log::Error(info);
		delete[] info;
		exit(EXIT_FAILURE);
	}
}


void ShaderProgram::Use(void) {
	glUseProgram(id);
}


void ShaderProgram::Stop(void) {
	glUseProgram(0);
}


void ShaderProgram::Delete(void) {
	glDeleteProgram(id);
}


int ShaderProgram::GetUniformLocation(const std::string &name) {
	return glGetUniformLocation(id, name.c_str());
}


void ShaderProgram::Uniform1d(const std::string &name, double v0) {
	int location = GetUniformLocation(name);
	glUniform1d(location, v0);
}


void ShaderProgram::Uniform2d(const std::string &name, double v0, double v1) {
	int location = GetUniformLocation(name);
	glUniform2d(location, v0, v1);
}


void ShaderProgram::Uniform3d(const std::string &name, double v0, double v1, double v2) {
	int location = GetUniformLocation(name);
	glUniform3d(location, v0, v1, v2);
}


void ShaderProgram::Uniform4d(const std::string &name, double v0, double v1, double v2, double v3) {
	int location = GetUniformLocation(name);
	glUniform4d(location, v0, v1, v2, v3);
}


void ShaderProgram::Uniform1dv(const std::string &name, int count, const double *value) {
	int location = GetUniformLocation(name);
	glUniform1dv(location, count, value);
}


void ShaderProgram::Uniform2dv(const std::string &name, int count, const double *value) {
	int location = GetUniformLocation(name);
	glUniform2dv(location, count, value);
}


void ShaderProgram::Uniform3dv(const std::string &name, int count, const double *value) {
	int location = GetUniformLocation(name);
	glUniform3dv(location, count, value);
}


void ShaderProgram::Uniform4dv(const std::string &name, int count, const double *value) {
	int location = GetUniformLocation(name);
	glUniform4dv(location, count, value);
}


void ShaderProgram::Uniform1f(const std::string &name, float v0) {
	int location = GetUniformLocation(name);
	glUniform1f(location, v0);
}


void ShaderProgram::Uniform2f(const std::string &name, float v0, float v1) {
	int location = GetUniformLocation(name);
	glUniform2f(location, v0, v1);
}


void ShaderProgram::Uniform3f(const std::string &name, float v0, float v1, float v2) {
	int location = GetUniformLocation(name);
	glUniform3f(location, v0, v1, v2);
}


void ShaderProgram::Uniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
	int location = GetUniformLocation(name);
	glUniform4f(location, v0, v1, v2, v3);
}


void ShaderProgram::Uniform1fv(const std::string &name, int count, const float *value) {
	int location = GetUniformLocation(name);
	glUniform1fv(location, count, value);
}


void ShaderProgram::Uniform2fv(const std::string &name, int count, const float *value) {
	int location = GetUniformLocation(name);
	glUniform2fv(location, count, value);
}


void ShaderProgram::Uniform3fv(const std::string &name, int count, const float *value) {
	int location = GetUniformLocation(name);
	glUniform3fv(location, count, value);
}


void ShaderProgram::Uniform4fv(const std::string &name, int count, const float *value) {
	int location = GetUniformLocation(name);
	glUniform4fv(location, count, value);
}


void ShaderProgram::Uniform1i(const std::string &name, int v0) {
	int location = GetUniformLocation(name);
	glUniform1i(location, v0);
}


void ShaderProgram::Uniform2i(const std::string &name, int v0, int v1) {
	int location = GetUniformLocation(name);
	glUniform2i(location, v0, v1);
}


void ShaderProgram::Uniform3i(const std::string &name, int v0, int v1, int v2) {
	int location = GetUniformLocation(name);
	glUniform3i(location, v0, v1, v2);
}


void ShaderProgram::Uniform4i(const std::string &name, int v0, int v1, int v2, int v3) {
	int location = GetUniformLocation(name);
	glUniform4i(location, v0, v1, v2, v3);
}


void ShaderProgram::Uniform1iv(const std::string &name, int count, const int *value) {
	int location = GetUniformLocation(name);
	glUniform1iv(location, count, value);
}


void ShaderProgram::Uniform2iv(const std::string &name, int count, const int *value) {
	int location = GetUniformLocation(name);
	glUniform2iv(location, count, value);
}


void ShaderProgram::Uniform3iv(const std::string &name, int count, const int *value) {
	int location = GetUniformLocation(name);
	glUniform3iv(location, count, value);
}


void ShaderProgram::Uniform4iv(const std::string &name, int count, const int *value) {
	int location = GetUniformLocation(name);
	glUniform4iv(location, count, value);
}


void ShaderProgram::Uniform1ui(const std::string &name, unsigned int v0) {
	int location = GetUniformLocation(name);
	glUniform1ui(location, v0);
}


void ShaderProgram::Uniform2ui(const std::string &name, unsigned int v0, unsigned int v1) {
	int location = GetUniformLocation(name);
	glUniform2ui(location, v0, v1);
}


void ShaderProgram::Uniform3ui(const std::string &name, unsigned int v0, unsigned int v1, unsigned int v2) {
	int location = GetUniformLocation(name);
	glUniform3ui(location, v0, v1, v2);
}


void ShaderProgram::Uniform4ui(const std::string &name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) {
	int location = GetUniformLocation(name);
	glUniform4ui(location, v0, v1, v2, v3);
}


void ShaderProgram::Uniform1uiv(const std::string &name, int count, const unsigned int *value) {
	int location = GetUniformLocation(name);
	glUniform1uiv(location, count, value);
}


void ShaderProgram::Uniform2uiv(const std::string &name, int count, const unsigned int *value) {
	int location = GetUniformLocation(name);
	glUniform2uiv(location, count, value);
}


void ShaderProgram::Uniform3uiv(const std::string &name, int count, const unsigned int *value) {
	int location = GetUniformLocation(name);
	glUniform3uiv(location, count, value);
}


void ShaderProgram::Uniform4uiv(const std::string &name, int count, const unsigned int *value) {
	int location = GetUniformLocation(name);
	glUniform4uiv(location, count, value);
}


void ShaderProgram::UniformMatrix2dv(const std::string &name, int count, bool transpose, const double *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix2dv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix2x3dv(const std::string &name, int count, bool transpose, const double *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix2x3dv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix2x4dv(const std::string &name, int count, bool transpose, const double *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix2x4dv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix3dv(const std::string &name, int count, bool transpose, const double *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix3dv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix3x2dv(const std::string &name, int count, bool transpose, const double *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix3x2dv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix3x4dv(const std::string &name, int count, bool transpose, const double *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix3x4dv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix4dv(const std::string &name, int count, bool transpose, const double *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix4dv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix4x2dv(const std::string &name, int count, bool transpose, const double *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix4x2dv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix4x3dv(const std::string &name, int count, bool transpose, const double *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix4x3dv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix2fv(const std::string &name, int count, bool transpose, const float *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix2fv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix2x3fv(const std::string &name, int count, bool transpose, const float *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix2x3fv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix2x4fv(const std::string &name, int count, bool transpose, const float *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix2x4fv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix3fv(const std::string &name, int count, bool transpose, const float *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix3fv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix3x2fv(const std::string &name, int count, bool transpose, const float *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix3x2fv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix3x4fv(const std::string &name, int count, bool transpose, const float *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix3x4fv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix4fv(const std::string &name, int count, bool transpose, const float *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix4fv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix4x2fv(const std::string &name, int count, bool transpose, const float *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix4x2fv(location, count, transpose, value);
}


void ShaderProgram::UniformMatrix4x3fv(const std::string &name, int count, bool transpose, const float *value) {
	int location = GetUniformLocation(name);
	glUniformMatrix4x3fv(location, count, transpose, value);
}