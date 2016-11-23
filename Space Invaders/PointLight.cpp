#include "PointLight.hpp"


PointLight::PointLight(void) {
	color = glm::vec3(0.0f, 0.0f, 0.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
}


PointLight::PointLight(const PointLight &pointLight) {
	color = pointLight.color;
	position = pointLight.position;
}


PointLight &PointLight::operator=(const PointLight &pointLight) {
	color = pointLight.color;
	position = pointLight.position;

	return *this;
}


PointLight::~PointLight(void) {
}


glm::vec3 PointLight::Color(void) {
	return color;
}


glm::vec3 PointLight::Position(void) {
	return position;
}


void PointLight::Color(const glm::vec3 &color) {
	this->color = color;
}


void PointLight::Position(const glm::vec3 &position) {
	this->position = position;
}