#pragma once

#include <glm/vec3.hpp>

#include "Agent.hpp"
#include "Weapon.hpp"

class Player : public Agent {
	Weapon weapon;

public:
	Player(const glm::vec3 &position);
	Player(const Player &player);
	Player &operator=(const Player &player);
	~Player(void);

public:
	void Update(float dt);
	void Fire(void);
	void FireColision(void);


public:
	Weapon GetWeapon(void);
};