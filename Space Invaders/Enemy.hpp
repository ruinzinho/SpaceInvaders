#pragma once

#include <glm/vec3.hpp>

#include "Agent.hpp"
#include "Weapon.hpp"

class Enemy : public Agent {
	Weapon middleWeapon;

public:
	Enemy(const glm::vec3 &position);
	Enemy(const Enemy &enemy);
	Enemy &operator=(const Enemy &enemy);
	~Enemy(void);

public:
	void Update(float dt);
	void Fire(void);

public:
	Weapon MiddleWeapon(void);
};