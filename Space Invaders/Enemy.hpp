#pragma once

#include <glm/vec3.hpp>

#include "Agent.hpp"
#include "Weapon.hpp"

class Enemy : public Agent {
	Weapon middleWeapon;

	float alpha;

public:
	Enemy(const glm::vec3 &position);
	Enemy(const Enemy &enemy);
	Enemy &operator=(const Enemy &enemy);
	~Enemy(void);

public:
	void Update(float dt);
	void Fire(void);
	void FireColision(void);

public:
	Weapon MiddleWeapon(void);

	glm::vec3 Direction(void);
	void Direction(glm::vec3 &direction);
	float Alpha(void);

	void Alpha(float alpha);
};