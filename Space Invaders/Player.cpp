#include "Player.hpp"

#include <glm/geometric.hpp>


Player::Player(const glm::vec3 &position) : Agent(position), weapon(position) {
}


Player::Player(const Player &player) : Agent(player), weapon(position) {
}


Player &Player::operator=(const Player &player) {
	Agent::operator=(player);
	weapon = player.weapon;

	return *this;
}


Player::~Player(void) {
}


void Player::Update(float dt) {
	glm::vec3 vel;
	glm::vec3 pos = position;

	vel = 4.0f * direction;
	pos = pos + vel * dt;

	if (!(pos.x < -14.0f || pos.x > 14.0f ||
		pos.z < 0.0f || pos.z > 19.0f)) {
		position = pos;
	}

	leftWeapon.Update(dt);
	rightWeapon.Update(dt);
}


void Player::Fire(void) {
	if (glm::length(weapon.Direction()) != 0.0f) {
		glm::vec3 direction(0.0f, 0.0f, -1.0f);

		weapon.Position(position + glm::vec3(-1.0f, 0.0f, 0.0f));

		weapon.Move(direction);
	}
}


Weapon Player::GetWeapon(void) {
	return weapon;
}