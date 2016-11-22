#include "Player.hpp"


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
	glm::vec3 velocity;

	velocity = 4.0f * direction;
	position = position + velocity * dt;
}


void Player::Fire(void) {
	glm::vec3 direction(0.0f, 0.0f, -1.0f);

	leftWeapon.Move(direction);
	rightWeapon.Move(direction);
}


Weapon Player::LeftWeapon(void) {
	return leftWeapon;
}


Weapon Player::RightWeapon(void) {
	return rightWeapon;
}