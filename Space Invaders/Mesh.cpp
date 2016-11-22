#include "Mesh.hpp"

#include <gl/glew.h>


Mesh::Mesh(void) {
	vertexArrayId = 0;
	bufferId = 0;
	elementBufferId = 0;

	elements = 0;
}


Mesh::Mesh(const Mesh &mesh) {
	vertexArrayId = mesh.vertexArrayId;
	bufferId = mesh.bufferId;
	elementBufferId = mesh.elementBufferId;
	elements = mesh.elements;
}


Mesh &Mesh::operator=(const Mesh &mesh) {
	vertexArrayId = mesh.vertexArrayId;
	bufferId = mesh.bufferId;
	elementBufferId = mesh.elementBufferId;
	elements = mesh.elements;

	return *this;
}


Mesh::~Mesh(void) {
}


void Mesh::Draw(void) {
	glBindVertexArray(vertexArrayId);
	glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}


void Mesh::Delete(void) {
	glDeleteBuffers(1, &bufferId);
	glDeleteBuffers(1, &elementBufferId);
	glDeleteVertexArrays(1, &vertexArrayId);
}


void Mesh::VertexArrayId(unsigned int vertexArrayId) {
	this->vertexArrayId = vertexArrayId;
}


void Mesh::BufferId(unsigned int bufferId) {
	this->bufferId = bufferId;
}


void Mesh::ElementBufferId(unsigned int elementBufferId) {
	this->elementBufferId = elementBufferId;
}


void Mesh::Elements(int elements) {
	this->elements = elements;
}