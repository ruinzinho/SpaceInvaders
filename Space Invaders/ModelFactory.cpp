#include "ModelFactory.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <gl/glew.h>

#include "Log.hpp"
#include "Mesh.hpp"


ModelFactory::ModelFactory(void) {
}


ModelFactory::ModelFactory(const ModelFactory &modelFactory) {
	models = modelFactory.models;
}


ModelFactory &ModelFactory::operator=(const ModelFactory &modelFactory) {
	models = modelFactory.models;

	return *this;
}


ModelFactory::~ModelFactory(void) {
}


void ModelFactory::Initialize(void) {
	Model &ak5 = CreateModelFromFile("AK_5_MODEL.3ds");
	Model &arc170 = CreateModelFromFile("ARC_170_MODEL.3ds");
	Model &plane = CreateModelFromFile("PLANE_MODEL.3ds");
	Model &laser = CreateModelFromFile("LASER_MODEL.3ds");

	models["AK_5_MODEL"] = ak5;
	models["ARC_170_MODEL"] = arc170;
	models["PLANE_MODEL"] = plane;
	models["LASER_MODEL"] = laser;
}


IDrawable &ModelFactory::AK5Model(void) {
	return models["AK_5_MODEL"];
}


IDrawable &ModelFactory::ARC170Model(void) {
	return models["ARC_170_MODEL"];
}


IDrawable &ModelFactory::PlaneModel(void){
	return models["PLANE_MODEL"];
}


IDrawable &ModelFactory::LaserModel(void){
	return models["LASER_MODEL"];
}


void ModelFactory::Delete(void) {
	for (std::pair<const std::string, Model> &keyValue : models) {
		Model &model = keyValue.second;
		model.Delete();
	}
}


Model ModelFactory::CreateModelFromFile(const std::string &filename) {
	Assimp::Importer importer;

	Log::Loading(filename);

	const aiScene *scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_CalcTangentSpace);
	if (scene == nullptr) {
		Log::Error(importer.GetErrorString());
		exit(EXIT_FAILURE);
	}

	Model model;

	for (unsigned int m = 0; m < scene->mNumMeshes; m++) {
		const aiMesh *assimpMesh = scene->mMeshes[m];

		const int numVertices = assimpMesh->mNumVertices;
		const int bufferSize = numVertices * sizeof(aiVector3D);

		const int numBuffers =
			(assimpMesh->HasPositions() ? 1 : 0) +
			(assimpMesh->HasTextureCoords(0) ? 1 : 0) +
			(assimpMesh->HasNormals() ? 1 : 0) +
			(assimpMesh->HasTangentsAndBitangents() ? 1 : 0);

		GLuint vertexArrayId = 0;

		glGenVertexArrays(1, &vertexArrayId);
		glBindVertexArray(vertexArrayId);

		GLuint bufferId = 0;

		glGenBuffers(1, &bufferId);
		glBindBuffer(GL_ARRAY_BUFFER, bufferId);
		glBufferData(GL_ARRAY_BUFFER, numBuffers * bufferSize, nullptr, GL_STATIC_DRAW);

		int offset = 0;

		if (assimpMesh->HasPositions()) {
			glBufferSubData(GL_ARRAY_BUFFER, offset, bufferSize, assimpMesh->mVertices);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)offset);

			offset = offset + bufferSize;
		}

		if (assimpMesh->HasTextureCoords(0)) {
			glBufferSubData(GL_ARRAY_BUFFER, offset, bufferSize, assimpMesh->mTextureCoords[0]);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)offset);

			offset = offset + bufferSize;
		}

		if (assimpMesh->HasNormals()) {
			glBufferSubData(GL_ARRAY_BUFFER, offset, bufferSize, assimpMesh->mNormals);
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)offset);

			offset = offset + bufferSize;
		}

		if (assimpMesh->HasTangentsAndBitangents()) {
			glBufferSubData(GL_ARRAY_BUFFER, offset, bufferSize, assimpMesh->mTangents);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)offset);

			offset = offset + bufferSize;
		}

		const unsigned int numFaces = assimpMesh->mNumFaces;
		const int elements = numFaces * 3;

		GLuint elementBufferId = 0;

		if (assimpMesh->HasFaces()) {
			GLuint *index = new GLuint[elements];

			for (unsigned int i = 0, j = 0; i < numFaces; i++) {
				index[j++] = assimpMesh->mFaces[i].mIndices[0];
				index[j++] = assimpMesh->mFaces[i].mIndices[1];
				index[j++] = assimpMesh->mFaces[i].mIndices[2];
			}

			glGenBuffers(1, &elementBufferId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements * sizeof(GLuint), index, GL_STATIC_DRAW);

			delete[] index;
		}

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		Mesh mesh;
		mesh.VertexArrayId(vertexArrayId);
		mesh.BufferId(bufferId);
		mesh.ElementBufferId(elementBufferId);
		mesh.Elements(elements);

		model.AddMesh(mesh);
	}

	return model;
}