#include "Model.hpp"


Model::Model(void) {
}


Model::Model(const Model &model) {
	meshes = model.meshes;
}


Model &Model::operator=(const Model &model) {
	meshes = model.meshes;

	return *this;
}


Model::~Model(void) {
}


void Model::Draw(void) {
	for (Mesh &mesh : meshes) {
		mesh.Draw();
	}
}


void Model::AddMesh(const Mesh &mesh) {
	meshes.push_back(mesh);
}


void Model::Delete(void) {
	for (Mesh &mesh : meshes) {
		mesh.Delete();
	}
}