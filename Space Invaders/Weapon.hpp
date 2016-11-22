#pragma once

#include <glm/vec3.hpp>

#include "Agent.hpp"

class Weapon : public Agent {
public:
	Weapon(const glm::vec3 &position);
	Weapon(const Weapon &weapon);
	Weapon &operator=(const Weapon &weapon);
	~Weapon(void);

public:
	void Update(float dt);
};