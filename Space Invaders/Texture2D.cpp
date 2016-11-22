#include "Texture2D.hpp"

#include <gl/glew.h>


Texture2D::Texture2D(void) : Texture() {
}


Texture2D::Texture2D(const Texture2D &texture2D) : Texture(texture2D) {
}


Texture2D &Texture2D::operator=(const Texture2D &texture2D) {
	Texture::operator=(texture2D);

	return *this;
}


Texture2D::~Texture2D(void) {
}


void Texture2D::Bind(void) {
	glActiveTexture(GL_TEXTURE0 + active);
	glBindTexture(GL_TEXTURE_2D, id);
}


void Texture2D::Unbind(void) {
	glActiveTexture(GL_TEXTURE0 + active);
	glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture2D::Delete(void) {
	glDeleteTextures(1, &id);
}


void Texture2D::Id(unsigned int id) {
	this->id = id;
}