#pragma once

#include <glm/vec3.hpp>

class PointLight {
	glm::vec3 position;
	glm::vec3 color;

public:
	PointLight(void);
	PointLight(const PointLight &pointLight);
	PointLight &operator=(const PointLight &pointLight);
	~PointLight(void);

public:
	glm::vec3 Color(void);
	glm::vec3 Position(void);

public:
	void Color(const glm::vec3 &color);
	void Position(const glm::vec3 &position);
};

