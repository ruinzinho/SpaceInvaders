#include "SpaceInvaders.hpp"


SpaceInvaders::SpaceInvaders(void) : player(glm::vec3(0.0f, 0.0f, 0.0f)) {
	paused = false;
	lives = 5;
	points = 0;
	enemiesDirection = glm::vec3(+1.0f, 0.0f, 0.0f);

	enemies.push_back(Enemy(glm::vec3(-11.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(-9.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(-7.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(-5.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(-3.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(-1.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(+1.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(+3.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(+5.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(+7.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(+9.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(+11.0f, 0.0f, -18.0f)));

	enemies.push_back(Enemy(glm::vec3(-11.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(-9.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(-7.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(-5.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(-3.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(-1.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(+1.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(+3.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(+5.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(+7.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(+9.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(+11.0f, 0.0f, -15.0f)));

	enemies.push_back(Enemy(glm::vec3(-11.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(-9.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(-7.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(-5.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(-3.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(-1.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(+1.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(+3.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(+5.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(+7.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(+9.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(+11.0f, 0.0f, -12.0f)));
}


SpaceInvaders::SpaceInvaders(const SpaceInvaders &spaceInvaders) : player(spaceInvaders.player) {
	paused = spaceInvaders.paused;
	lives = spaceInvaders.lives;
	points = spaceInvaders.points;
	enemies = spaceInvaders.enemies;
	enemiesDirection = spaceInvaders.enemiesDirection;
}


SpaceInvaders &SpaceInvaders::operator=(const SpaceInvaders &spaceInvaders) {
	paused = spaceInvaders.paused;
	lives = spaceInvaders.lives;
	points = spaceInvaders.points;
	player = spaceInvaders.player;
	enemies = spaceInvaders.enemies;
	enemiesDirection = spaceInvaders.enemiesDirection;

	return *this;
}


SpaceInvaders::~SpaceInvaders(void) {
}


void SpaceInvaders::Update(float dt) {
	if (paused) {
		dt = 0;
	}

	player.Update(dt);

	for (Enemy &enemy : enemies) {
		enemy.Direction(enemiesDirection);
		enemy.Update(dt);
		if (enemy.Direction() != enemiesDirection)
			enemiesDirection = enemiesDirection * -1.0f;
	}

}


void SpaceInvaders::Move(float x, float y, float z) {
	player.Move(glm::vec3(x, y, z));
}


void SpaceInvaders::Fire(void) {
	player.Fire();
}


void SpaceInvaders::Pause(void) {
	paused = true;
}


void SpaceInvaders::Resume(void) {
	paused = false;
}


void SpaceInvaders::Restart(void) {
	// TODO: reset agents position
	paused = false;
	lives = 5;
	points = 0;

	player.Position(glm::vec3(0.0f, 0.0f, 0.0f));

	enemiesDirection = glm::vec3(+1.0f, 0.0f, 0.0f);

	enemies.clear();
	enemies.push_back(Enemy(glm::vec3(-11.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(-9.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(-7.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(-5.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(-3.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(-1.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(+1.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(+3.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(+5.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(+7.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(+9.0f, 0.0f, -18.0f)));
	enemies.push_back(Enemy(glm::vec3(+11.0f, 0.0f, -18.0f)));

	enemies.push_back(Enemy(glm::vec3(-11.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(-9.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(-7.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(-5.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(-3.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(-1.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(+1.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(+3.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(+5.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(+7.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(+9.0f, 0.0f, -15.0f)));
	enemies.push_back(Enemy(glm::vec3(+11.0f, 0.0f, -15.0f)));

	enemies.push_back(Enemy(glm::vec3(-11.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(-9.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(-7.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(-5.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(-3.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(-1.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(+1.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(+3.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(+5.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(+7.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(+9.0f, 0.0f, -12.0f)));
	enemies.push_back(Enemy(glm::vec3(+11.0f, 0.0f, -12.0f)));
}


int SpaceInvaders::Lives(void) {
	return lives;
}


int SpaceInvaders::Points(void) {
	return points;
}


bool SpaceInvaders::Paused(void) {
	return paused;
}


Player SpaceInvaders::Players(void) {
	return player;
}


std::vector<Enemy> SpaceInvaders::Enemies(void) {
	return enemies;
}