#include "VertexShader.hpp"

#include <gl/glew.h>


VertexShader::VertexShader(void) : Shader() {
}


VertexShader::VertexShader(const VertexShader &vertexShader) : Shader(vertexShader) {
}


VertexShader &VertexShader::operator=(const VertexShader &vertexShader) {
	Shader::operator=(vertexShader);

	return *this;
}


VertexShader::~VertexShader(void) {
}


void VertexShader::Create(void) {
	id = glCreateShader(GL_VERTEX_SHADER);
}