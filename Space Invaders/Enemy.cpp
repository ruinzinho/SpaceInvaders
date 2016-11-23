#include "Enemy.hpp"



Enemy::Enemy(const glm::vec3 &position) : Agent(position), middleWeapon(position) {
	alpha = 1.0f;
}


Enemy::Enemy(const Enemy &enemy) : Agent(enemy), middleWeapon(enemy.middleWeapon) {
	alpha = 1.0f;
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

	if (position.x <= -14.0f || position.x >= 14.0f) {
		direction = direction * -1.0f;
	}
}


void Enemy::Fire(void) {
	glm::vec3 direction(0.0f, 0.0f, 1.0f);

	middleWeapon.Move(direction);
}


void Enemy::FireColision() {
	if (alpha != 0.0f)
		alpha -= 0.5f;
}


Weapon Enemy::MiddleWeapon(void) {
	return middleWeapon;
}

glm::vec3 Enemy::Direction(void) {
	return direction;
}

void Enemy::Direction(glm::vec3 & direction) {
	this->direction = direction;
}


float Enemy::Alpha() {
	return alpha;
}


void Enemy::Alpha(float alpha) {
	this->alpha = alpha;
}
