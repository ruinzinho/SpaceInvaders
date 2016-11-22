#pragma once

#include <string>
#include <map>

#include "IDrawable.hpp"
#include "Model.hpp"

class ModelFactory {
	std::map<std::string, Model> models;

public:
	ModelFactory(void);
	ModelFactory(const ModelFactory &modelFactory);
	ModelFactory &operator=(const ModelFactory &modelFactory);
	~ModelFactory(void);

public:
	void Initialize(void);

public:
	IDrawable &AK5Model(void);
	IDrawable &ARC170Model(void);
	IDrawable &PlaneModel(void);
	IDrawable &LaserModel(void);

public:
	void Delete(void);

private:
	Model CreateModelFromFile(const std::string &filename);
};