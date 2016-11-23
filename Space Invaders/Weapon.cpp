#include "Weapon.hpp"

#include <glm/geometric.hpp>


Weapon::Weapon(const glm::vec3 &position) : Agent(position) {
}


Weapon::Weapon(const Weapon &weapon) : Agent(weapon) {
}


Weapon &Weapon::operator=(const Weapon &weapon) {
	Agent::operator=(weapon);

	return *this;
}


Weapon::~Weapon(void) {
}


void Weapon::Update(float dt) {
	glm::vec3 velocity;

	velocity = 15.0f * direction;
	position = position + velocity * dt;

	if (position.z <= -20.0f) {
		direction = glm::vec3(0.0f, 0.0f, 0.0f);
	}
}


glm::vec3 Weapon::Position(void) {
	return position;
}


void Weapon::Position(const glm::vec3 &position) {
	this->position = position;
}