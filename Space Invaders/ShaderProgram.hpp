#pragma once

#include <string>

#include "IProgram.hpp"
#include "Shader.hpp"

class ShaderProgram : public IProgram {
	unsigned int id;

public:
	ShaderProgram(void);
	ShaderProgram(const ShaderProgram &shaderProgram);
	ShaderProgram &operator=(const ShaderProgram &shaderProgram);
	~ShaderProgram(void);

public:
	void Create(void);
	void AttachShader(Shader &shader);
	void BindAttribLocation(unsigned int index, const std::string &name);
	void Link(void);
	void Use(void);
	void Stop(void);
	void Delete(void);

private:
	int GetUniformLocation(const std::string &name);

public:
	void Uniform1d(const std::string &name, double v0);
	void Uniform2d(const std::string &name, double v0, double v1);
	void Uniform3d(const std::string &name, double v0, double v1, double v2);
	void Uniform4d(const std::string &name, double v0, double v1, double v2, double v3);

public:
	void Uniform1dv(const std::string &name, int count, const double *value);
	void Uniform2dv(const std::string &name, int count, const double *value);
	void Uniform3dv(const std::string &name, int count, const double *value);
	void Uniform4dv(const std::string &name, int count, const double *value);

public:
	void Uniform1f(const std::string &name, float v0);
	void Uniform2f(const std::string &name, float v0, float v1);
	void Uniform3f(const std::string &name, float v0, float v1, float v2);
	void Uniform4f(const std::string &name, float v0, float v1, float v2, float v3);

public:
	void Uniform1fv(const std::string &name, int count, const float *value);
	void Uniform2fv(const std::string &name, int count, const float *value);
	void Uniform3fv(const std::string &name, int count, const float *value);
	void Uniform4fv(const std::string &name, int count, const float *value);

public:
	void Uniform1i(const std::string &name, int v0);
	void Uniform2i(const std::string &name, int v0, int v1);
	void Uniform3i(const std::string &name, int v0, int v1, int v2);
	void Uniform4i(const std::string &name, int v0, int v1, int v2, int v3);

public:
	void Uniform1iv(const std::string &name, int count, const int *value);
	void Uniform2iv(const std::string &name, int count, const int *value);
	void Uniform3iv(const std::string &name, int count, const int *value);
	void Uniform4iv(const std::string &name, int count, const int *value);

public:
	void Uniform1ui(const std::string &name, unsigned int v0);
	void Uniform2ui(const std::string &name, unsigned int v0, unsigned int v1);
	void Uniform3ui(const std::string &name, unsigned int v0, unsigned int v1, unsigned int v2);
	void Uniform4ui(const std::string &name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);

public:
	void Uniform1uiv(const std::string &name, int count, const unsigned int *value);
	void Uniform2uiv(const std::string &name, int count, const unsigned int *value);
	void Uniform3uiv(const std::string &name, int count, const unsigned int *value);
	void Uniform4uiv(const std::string &name, int count, const unsigned int *value);

public:
	void UniformMatrix2dv(const std::string &name, int count, bool transpose, const double *value);
	void UniformMatrix2x3dv(const std::string &name, int count, bool transpose, const double *value);
	void UniformMatrix2x4dv(const std::string &name, int count, bool transpose, const double *value);
	void UniformMatrix3dv(const std::string &name, int count, bool transpose, const double *value);
	void UniformMatrix3x2dv(const std::string &name, int count, bool transpose, const double *value);
	void UniformMatrix3x4dv(const std::string &name, int count, bool transpose, const double *value);
	void UniformMatrix4dv(const std::string &name, int count, bool transpose, const double *value);
	void UniformMatrix4x2dv(const std::string &name, int count, bool transpose, const double *value);
	void UniformMatrix4x3dv(const std::string &name, int count, bool transpose, const double *value);

public:
	void UniformMatrix2fv(const std::string &name, int count, bool transpose, const float *value);
	void UniformMatrix2x3fv(const std::string &name, int count, bool transpose, const float *value);
	void UniformMatrix2x4fv(const std::string &name, int count, bool transpose, const float *value);
	void UniformMatrix3fv(const std::string &name, int count, bool transpose, const float *value);
	void UniformMatrix3x2fv(const std::string &name, int count, bool transpose, const float *value);
	void UniformMatrix3x4fv(const std::string &name, int count, bool transpose, const float *value);
	void UniformMatrix4fv(const std::string &name, int count, bool transpose, const float *value);
	void UniformMatrix4x2fv(const std::string &name, int count, bool transpose, const float *value);
	void UniformMatrix4x3fv(const std::string &name, int count, bool transpose, const float *value);
};