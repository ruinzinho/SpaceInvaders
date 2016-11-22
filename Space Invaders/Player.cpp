#include "Player.hpp"

#include <glm/geometric.hpp>


Player::Player(const glm::vec3 &position) : Agent(position), leftWeapon(position + glm::vec3(-0.5f, 0.0f, 0.0f)), rightWeapon(position + glm::vec3(0.5f, 0.0f, 0.0f)) {
}


Player::Player(const Player &player) : Agent(player), leftWeapon(leftWeapon), rightWeapon(rightWeapon) {
}


Player &Player::operator=(const Player &player) {
	Agent::operator=(player);
	leftWeapon = player.leftWeapon;
	rightWeapon = player.rightWeapon;

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
}


void Player::Fire(void) {
	if (glm::length(leftWeapon.Direction()) != 0.0f && glm::length(rightWeapon.Direction()) != 0.0f) {
		glm::vec3 direction(0.0f, 0.0f, -1.0f);

		leftWeapon.Position(position + glm::vec3(-1.0f, 0.0f, 0.0f));
		rightWeapon.Position(position + glm::vec3(1.0f, 0.0f, 0.0f));

		leftWeapon.Move(direction);
		rightWeapon.Move(direction);
	}
}


Weapon Player::LeftWeapon(void) {
	return leftWeapon;
}


Weapon Player::RightWeapon(void) {
	return rightWeapon;
}