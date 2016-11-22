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

	velocity = 5.0f * direction;
	position = position + velocity * dt;
}


void Weapon::Position(const glm::vec3 &position) {
	this->position = position;
}