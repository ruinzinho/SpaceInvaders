#pragma once

#include <vector>

#include "IDrawable.hpp"
#include "Mesh.hpp"

class Model : public IDrawable {
	std::vector<Mesh> meshes;

public:
	Model(void);
	Model(const Model &model);
	Model &operator=(const Model &model);
	~Model(void);

public:
	void Draw(void);

public:
	void AddMesh(const Mesh &mesh);
	void Delete(void);
};