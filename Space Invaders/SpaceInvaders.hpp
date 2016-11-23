#pragma once

#include <vector>

#include "Enemy.hpp"
#include "Player.hpp"

class SpaceInvaders {
	bool paused;
	int lives;
	int points;

	Player player;
	std::vector<Enemy> enemies;
	glm::vec3 enemiesDirection;
	
public:
	SpaceInvaders(void);
	SpaceInvaders(const SpaceInvaders &spaceInvaders);
	SpaceInvaders &operator=(const SpaceInvaders &spaceInvaders);
	~SpaceInvaders(void);

public:
	void Update(float dt);
	void Move(float x, float y, float z);
	void Fire(void);
	void Pause(void);
	void Resume(void);
	void Restart(void);

public:
	int Lives(void);
	int Points(void);
	bool Paused(void);

	Player Players(void);
	std::vector<Enemy> Enemies(void);
};