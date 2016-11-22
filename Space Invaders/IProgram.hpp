#pragma once

#include <string>

class IProgram {
public:
	virtual void Use(void) = 0;
	virtual void Stop(void) = 0;

public:
	virtual void Uniform1d(const std::string &name, double v0) = 0;
	virtual void Uniform2d(const std::string &name, double v0, double v1) = 0;
	virtual void Uniform3d(const std::string &name, double v0, double v1, double v2) = 0;
	virtual void Uniform4d(const std::string &name, double v0, double v1, double v2, double v3) = 0;

public:
	virtual void Uniform1dv(const std::string &name, int count, const double *value) = 0;
	virtual void Uniform2dv(const std::string &name, int count, const double *value) = 0;
	virtual void Uniform3dv(const std::string &name, int count, const double *value) = 0;
	virtual void Uniform4dv(const std::string &name, int count, const double *value) = 0;

public:
	virtual void Uniform1f(const std::string &name, float v0) = 0;
	virtual void Uniform2f(const std::string &name, float v0, float v1) = 0;
	virtual void Uniform3f(const std::string &name, float v0, float v1, float v2) = 0;
	virtual void Uniform4f(const std::string &name, float v0, float v1, float v2, float v3) = 0;

public:
	virtual void Uniform1fv(const std::string &name, int count, const float *value) = 0;
	virtual void Uniform2fv(const std::string &name, int count, const float *value) = 0;
	virtual void Uniform3fv(const std::string &name, int count, const float *value) = 0;
	virtual void Uniform4fv(const std::string &name, int count, const float *value) = 0;

public:
	virtual void Uniform1i(const std::string &name, int v0) = 0;
	virtual void Uniform2i(const std::string &name, int v0, int v1) = 0;
	virtual void Uniform3i(const std::string &name, int v0, int v1, int v2) = 0;
	virtual void Uniform4i(const std::string &name, int v0, int v1, int v2, int v3) = 0;

public:
	virtual void Uniform1iv(const std::string &name, int count, const int *value) = 0;
	virtual void Uniform2iv(const std::string &name, int count, const int *value) = 0;
	virtual void Uniform3iv(const std::string &name, int count, const int *value) = 0;
	virtual void Uniform4iv(const std::string &name, int count, const int *value) = 0;

public:
	virtual void Uniform1ui(const std::string &name, unsigned int v0) = 0;
	virtual void Uniform2ui(const std::string &name, unsigned int v0, unsigned int v1) = 0;
	virtual void Uniform3ui(const std::string &name, unsigned int v0, unsigned int v1, unsigned int v2) = 0;
	virtual void Uniform4ui(const std::string &name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3) = 0;

public:
	virtual void Uniform1uiv(const std::string &name, int count, const unsigned int *value) = 0;
	virtual void Uniform2uiv(const std::string &name, int count, const unsigned int *value) = 0;
	virtual void Uniform3uiv(const std::string &name, int count, const unsigned int *value) = 0;
	virtual void Uniform4uiv(const std::string &name, int count, const unsigned int *value) = 0;

public:
	virtual void UniformMatrix2dv(const std::string &name, int count, bool transpose, const double *value) = 0;
	virtual void UniformMatrix2x3dv(const std::string &name, int count, bool transpose, const double *value) = 0;
	virtual void UniformMatrix2x4dv(const std::string &name, int count, bool transpose, const double *value) = 0;
	virtual void UniformMatrix3dv(const std::string &name, int count, bool transpose, const double *value) = 0;
	virtual void UniformMatrix3x2dv(const std::string &name, int count, bool transpose, const double *value) = 0;
	virtual void UniformMatrix3x4dv(const std::string &name, int count, bool transpose, const double *value) = 0;
	virtual void UniformMatrix4dv(const std::string &name, int count, bool transpose, const double *value) = 0;
	virtual void UniformMatrix4x2dv(const std::string &name, int count, bool transpose, const double *value) = 0;
	virtual void UniformMatrix4x3dv(const std::string &name, int count, bool transpose, const double *value) = 0;

public:
	virtual void UniformMatrix2fv(const std::string &name, int count, bool transpose, const float *value) = 0;
	virtual void UniformMatrix2x3fv(const std::string &name, int count, bool transpose, const float *value) = 0;
	virtual void UniformMatrix2x4fv(const std::string &name, int count, bool transpose, const float *value) = 0;
	virtual void UniformMatrix3fv(const std::string &name, int count, bool transpose, const float *value) = 0;
	virtual void UniformMatrix3x2fv(const std::string &name, int count, bool transpose, const float *value) = 0;
	virtual void UniformMatrix3x4fv(const std::string &name, int count, bool transpose, const float *value) = 0;
	virtual void UniformMatrix4fv(const std::string &name, int count, bool transpose, const float *value) = 0;
	virtual void UniformMatrix4x2fv(const std::string &name, int count, bool transpose, const float *value) = 0;
	virtual void UniformMatrix4x3fv(const std::string &name, int count, bool transpose, const float *value) = 0;
};