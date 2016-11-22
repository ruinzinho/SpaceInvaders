#pragma once

class Texture {
protected:
	unsigned int id;
	unsigned int active;

public:
	Texture(void);
	Texture(const Texture &texture);
	Texture &operator=(const Texture &texture);
	~Texture(void);

public:
	void Active(unsigned int active);

public:
	virtual void Bind(void) = 0;
	virtual void Unbind(void) = 0;
};