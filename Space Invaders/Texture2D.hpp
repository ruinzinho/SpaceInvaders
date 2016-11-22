#pragma once

#include "Texture.hpp"

class Texture2D : public Texture {
public:
	Texture2D(void);
	Texture2D(const Texture2D &texture2D);
	Texture2D &operator=(const Texture2D &texture2D);
	~Texture2D(void);

public:
	void Bind(void);
	void Unbind(void);
	void Delete(void);

public:
	void Id(unsigned int id);
};

