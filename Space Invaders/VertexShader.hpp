#pragma once

#include "Shader.hpp"

class VertexShader : public Shader {
public:
	VertexShader(void);
	VertexShader(const VertexShader &vertexShader);
	VertexShader &operator=(const VertexShader &vertexShader);
	~VertexShader(void);

public:
	void Create(void);
};