#include "FragmentShader.hpp"

#include <gl/glew.h>


FragmentShader::FragmentShader(void) : Shader() {
}


FragmentShader::FragmentShader(const FragmentShader &fragmentShader) : Shader(fragmentShader) {
}


FragmentShader &FragmentShader::operator=(const FragmentShader &fragmentShader) {
	Shader::operator=(fragmentShader);

	return *this;
}


FragmentShader::~FragmentShader(void) {
}


void FragmentShader::Create(void) {
	id = glCreateShader(GL_FRAGMENT_SHADER);
}