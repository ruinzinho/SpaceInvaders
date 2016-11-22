#pragma once

#include "IDrawable.hpp"

class Mesh : public IDrawable {
	unsigned int vertexArrayId;
	unsigned int bufferId;
	unsigned int elementBufferId;

	int elements;

public:
	Mesh(void);
	Mesh(const Mesh &mesh);
	Mesh &operator=(const Mesh &mesh);
	~Mesh(void);

public:
	void Draw(void);
	void Delete(void);

public:
	void VertexArrayId(unsigned int vertexArrayId);
	void BufferId(unsigned int bufferId);
	void ElementBufferId(unsigned int elementBufferId);
	void Elements(int elements);
};