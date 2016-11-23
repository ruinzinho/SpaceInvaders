#include "Player.hpp"

#include <glm/geometric.hpp>


Player::Player(const glm::vec3 &position) : Agent(position), weapon(position) {
}


Player::Player(const Player &player) : Agent(player), weapon(player.weapon) {
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

	vel = 5.0f * direction;
	pos = pos + vel * dt;

	if (!(pos.x < -14.0f || pos.x > 14.0f ||
		pos.z < 0.0f || pos.z > 19.0f)) {
		position = pos;
	}
	weapon.Update(dt);
	if (weapon.Direction() == glm::vec3(0.0f, 0.0f, 0.0f)) {
		weapon.Position(position);
	}
}


void Player::Fire(void) {
	if (weapon.Direction() == glm::vec3(0.0f, 0.0f, 0.0f)) {
		weapon.Position(position);
		weapon.Direction(glm::vec3(0.0f, 0.0f, -1.0f));
	}
}


void Player::FireColision() {
	weapon.Position(position);
	weapon.Direction(glm::vec3(0.0f, 0.0f, 0.0f));
}


void Player::Position(const glm::vec3 &position) {
	this->position = position;
}


Weapon Player::GetWeapon(void) {
	return weapon;
}


glm::vec3 Player::Position(void) {
	return position;
}