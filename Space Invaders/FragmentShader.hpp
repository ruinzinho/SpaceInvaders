#pragma once

#include "Shader.hpp"

class FragmentShader : public Shader {
public:
	FragmentShader(void);
	FragmentShader(const FragmentShader &fragmentShader);
	FragmentShader &operator=(const FragmentShader &fragmentShader);
	~FragmentShader(void);

public:
	void Create(void);
};