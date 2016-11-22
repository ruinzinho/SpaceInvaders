#include "Texture.hpp"


Texture::Texture(void) {
	id = 0;
	active = 0;
}


Texture::Texture(const Texture &texture) {
	id = texture.id;
	active = texture.active;
}


Texture &Texture::operator=(const Texture &texture) {
	id = texture.id;
	active = texture.active;

	return *this;
}


Texture::~Texture(void) {
}


void Texture::Active(unsigned int active) {
	this->active = active;
}