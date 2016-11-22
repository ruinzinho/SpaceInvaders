#pragma once

#include <string>

class Shader {
protected:
	unsigned int id;

public:
	Shader(void);
	Shader(const Shader &shader);
	Shader &operator=(const Shader &shader);
	~Shader(void);

public:
	virtual void Create(void) = 0;

public:
	void Compile(const std::string &code);
	void Delete(void);

public:
	unsigned int Id(void);
};