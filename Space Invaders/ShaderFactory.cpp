#include "ShaderFactory.hpp"

#include <fstream>
#include <sstream>

#include "FragmentShader.hpp"
#include "Log.hpp"
#include "VertexShader.hpp"


ShaderFactory::ShaderFactory(void) {
}


ShaderFactory::ShaderFactory(const ShaderFactory &shaderFactory) {
	shaderPrograms = shaderFactory.shaderPrograms;
}


ShaderFactory &ShaderFactory::operator=(const ShaderFactory &shaderFactory) {
	shaderPrograms = shaderFactory.shaderPrograms;

	return *this;
}


ShaderFactory::~ShaderFactory(void) {
}


void ShaderFactory::Initialize(void) {
	ShaderProgram &ilumination = CreateShaderProgramFromFile("ILUMINATION_SHADER.vert", "ILUMINATION_SHADER.frag");

	ilumination.BindAttribLocation(0, "in_Position");
	ilumination.BindAttribLocation(1, "in_Texcoord");
	ilumination.BindAttribLocation(2, "in_Normal");
	ilumination.BindAttribLocation(3, "in_Tangent");

	ilumination.Link();

	shaderPrograms["ILUMINATION_SHADER"] = ilumination;
}


IProgram &ShaderFactory::IluminationShader(void) {
	return shaderPrograms["ILUMINATION_SHADER"];
}


void ShaderFactory::Delete(void) {
	for (std::pair<const std::string, ShaderProgram> &keyValue : shaderPrograms) {
		ShaderProgram &program = keyValue.second;
		program.Delete();
	}
}


std::string ShaderFactory::ReadFromFile(const std::string &filename) {
	std::ifstream file(filename);

	if (file.is_open() == false) {
		Log::Error("Couldn't open " + filename);
		exit(EXIT_FAILURE);
	}

	Log::Loading(filename);

	std::stringstream stream;
	stream << file.rdbuf();
	file.close();

	return stream.str();
}


ShaderProgram ShaderFactory::CreateShaderProgramFromFile(const std::string &vert, const std::string &frag) {
	VertexShader vertexShader;
	vertexShader.Create();
	vertexShader.Compile(ReadFromFile(vert));

	FragmentShader fragmentShader;
	fragmentShader.Create();
	fragmentShader.Compile(ReadFromFile(frag));

	ShaderProgram program;

	program.Create();

	program.AttachShader(vertexShader);
	program.AttachShader(fragmentShader);

	return program;
}