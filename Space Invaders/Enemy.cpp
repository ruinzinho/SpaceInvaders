#include "Enemy.hpp"


Enemy::Enemy(const glm::vec3 &position) : Agent(position), middleWeapon(position) {
}


Enemy::Enemy(const Enemy &enemy) : Agent(enemy), middleWeapon(enemy.middleWeapon) {
}


Enemy &Enemy::operator=(const Enemy &enemy) {
	Agent::operator=(enemy);
	middleWeapon = enemy.middleWeapon;

	return *this;
}


Enemy::~Enemy(void) {
}


void Enemy::Update(float dt) {
	glm::vec3 velocity;

	velocity = 1.0f * direction;
	position = position + velocity * dt;
}


void Enemy::Fire(void) {
	glm::vec3 direction(0.0f, 0.0f, 1.0f);

	middleWeapon.Move(direction);
}


Weapon Enemy::MiddleWeapon(void) {
	return middleWeapon;
}