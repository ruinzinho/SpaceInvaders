#pragma once

#include <glm/vec3.hpp>

class Agent {
protected:
	glm::vec3 position;
	glm::vec3 direction;

public:
	Agent(const glm::vec3 &position);
	Agent(const Agent &agent);
	Agent &operator=(const Agent &agent);
	~Agent(void);

public:
	virtual void Update(float dt) = 0;

public:
	void Move(const glm::vec3 &direction);

public:
	glm::vec3 Position(void);
};