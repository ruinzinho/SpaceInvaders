#include "Agent.hpp"

#include <glm/geometric.hpp>


Agent::Agent(const glm::vec3 &position) {
	this->position = position;
	this->direction = glm::vec3(0.0f, 0.0f, 0.0f);
}


Agent::Agent(const Agent &agent) {
	position = agent.position;
	direction = agent.direction;
}


Agent &Agent::operator=(const Agent &agent) {
	position = agent.position;
	direction = agent.direction;

	return *this;
}


Agent::~Agent(void) {
}


void Agent::Move(const glm::vec3 &direction) {
	glm::vec3 dir = this->direction;
	dir = dir + glm::normalize(direction);

	if (glm::length(dir) != 0.0f) {
		dir = glm::normalize(dir);
	}

	this->direction = dir;
}


glm::vec3 Agent::Position(void) {
	return position;
}