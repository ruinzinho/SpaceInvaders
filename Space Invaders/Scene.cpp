#include "Scene.hpp"

#include <gl/glew.h>

#include <glm/gtc/matrix_transform.hpp>


Scene::Scene(void) {
	cameraType = CameraType::FIXED_PERSPECTIVE;

	aspect = 1;
}


Scene::Scene(const Scene &scene) {
	projectionMatrix = scene.projectionMatrix;
	viewMatrix = scene.viewMatrix;
	modelFactory = scene.modelFactory;
	shaderFactory = scene.shaderFactory;
	textureFactory = scene.textureFactory;
}


Scene &Scene::operator=(const Scene &scene) {
	projectionMatrix = scene.projectionMatrix;
	viewMatrix = scene.viewMatrix;
	modelFactory = scene.modelFactory;
	shaderFactory = scene.shaderFactory;
	textureFactory = scene.textureFactory;

	return *this;
}


Scene::~Scene(void) {
}


void Scene::Initialize(void) {
	modelFactory.Initialize();
	shaderFactory.Initialize();
	textureFactory.Initialize();
}


void Scene::Reshape(int width, int height) {
	aspect = static_cast<float>(width) / height;
}


void Scene::Render(SpaceInvaders &spaceInvaders) {
	Player player = spaceInvaders.Players();

	switch (cameraType) {
	case Scene::CameraType::FIXED_OTHOGONAL:
		projectionMatrix = glm::ortho(-10.0f * aspect, 10.0f * aspect, 0.0f, 20.0f, 0.0f, 10.0f);
		viewMatrix = glm::lookAt(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		break;
	case Scene::CameraType::FIXED_PERSPECTIVE:
		projectionMatrix = glm::perspective(glm::radians(60.0f), aspect, 1.0f, 50.0f);
		viewMatrix = glm::lookAt(glm::vec3(0.0f, 9.5f, 6.0f), glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	case Scene::CameraType::FLEXIBLE_PERSPECTIVE:
		projectionMatrix = glm::perspective(glm::radians(45.0f), aspect, 1.0f, 50.0f);
		viewMatrix = glm::lookAt(player.Position() + glm::vec3(1.0f, 5.0f, 3.5f), player.Position() + glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		break;
	}

	DrawPlayer(spaceInvaders, glm::mat4(1.0f));
	DrawEnemies(spaceInvaders, glm::mat4(1.0f));

	glEnable(GL_STENCIL_TEST);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xFF);
	glDepthMask(GL_FALSE);
	glClear(GL_STENCIL_BUFFER_BIT);

	DrawFloor(spaceInvaders, glm::mat4(1.0f));

	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilMask(0x00);
	glDepthMask(GL_TRUE);

	glCullFace(GL_FRONT);
	DrawPlayer(spaceInvaders, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 1.0f)), 0.5f);
	DrawEnemies(spaceInvaders, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, 1.0f)), 0.5f);
	glCullFace(GL_BACK);

	glDisable(GL_STENCIL_TEST);
}


void Scene::Delete(void) {
	modelFactory.Delete();
	shaderFactory.Delete();
	textureFactory.Delete();
}


void Scene::FixedOrthogonal(void) {
	// Removed
	// cameraType = CameraType::FIXED_OTHOGONAL;
}


void Scene::FixedPerspective(void) {
	cameraType = CameraType::FIXED_PERSPECTIVE;
}


void Scene::FlexiblePerspective(void) {
	cameraType = CameraType::FLEXIBLE_PERSPECTIVE;
}


void Scene::TogglePointLights(void) {
}


void Scene::ToggleSpotLight(void) {
}


void Scene::ToggleDirectionalLight(void) {
}


void Scene::DrawPlayer(SpaceInvaders &spaceInvaders, const glm::mat4 &matrix, float alpha) {
	IProgram &program = shaderFactory.IluminationShader();

	program.Use();

	glm::vec3 lightPosition = viewMatrix * glm::vec4(0.0f, 3.0f, -7.5f, 1.0f);

	program.Uniform3fv("light.position", 1, &lightPosition[0]);
	program.Uniform3f("light.color", 1.0f, 1.0f, 1.0f);

	Player player = spaceInvaders.Players();

	Texture &emissionTexture = textureFactory.BlackTexture();
	Texture &diffuseTexture = textureFactory.ARC170DiffuseTexture();
	Texture &specularTexture = textureFactory.ARC170SpecularTexture();
	Texture &normalTexture = textureFactory.ARC170NormalTexture();
	IDrawable &model = modelFactory.ARC170Model();

	emissionTexture.Active(0);
	emissionTexture.Bind();

	program.Uniform1i("emissiontexture", 0);

	diffuseTexture.Active(1);
	diffuseTexture.Bind();

	program.Uniform1i("diffusetexture", 1);

	specularTexture.Active(2);
	specularTexture.Bind();

	program.Uniform1i("speculartexture", 2);

	normalTexture.Active(3);
	normalTexture.Bind();

	program.Uniform1i("normaltexture", 3);

	program.Uniform3f("material.emission", 0.0f, 0.0f, 0.0f);
	program.Uniform3f("material.ambient", 0.1f, 0.1f, 0.1f);
	program.Uniform3f("material.diffuse", 1.0f, 1.0f, 1.0f);
	program.Uniform3f("material.specular", 0.5f, 0.5f, 0.5f);
	program.Uniform1i("material.shininess", 20);
	program.Uniform1f("material.alpha", alpha);

	glm::mat4 modelMatrix = glm::translate(matrix, glm::vec3(0.0f, 0.5f, -1.0f));
	modelMatrix = glm::translate(modelMatrix, player.Position());

	glm::mat4 textureMatrix = glm::mat4(1.0f);

	glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
	glm::mat4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;
	glm::mat4 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelViewMatrix)));

	program.UniformMatrix4fv("NormalMatrix", 1, false, &normalMatrix[0][0]);
	program.UniformMatrix4fv("TextureMatrix", 1, false, &textureMatrix[0][0]);
	program.UniformMatrix4fv("ModelViewMatrix", 1, false, &modelViewMatrix[0][0]);
	program.UniformMatrix4fv("ModelViewProjectionMatrix", 1, false, &modelViewProjectionMatrix[0][0]);

	model.Draw();

	normalTexture.Unbind();
	specularTexture.Unbind();
	diffuseTexture.Unbind();
	emissionTexture.Unbind();

	program.Stop();
}


void Scene::DrawEnemies(SpaceInvaders &spaceInvaders, const glm::mat4 &matrix, float alpha) {
	IProgram &program = shaderFactory.IluminationShader();

	program.Use();

	glm::vec3 lightPosition = viewMatrix * glm::vec4(0.0f, 3.0f, -7.5f, 1.0f);

	program.Uniform3fv("light.position", 1, &lightPosition[0]);
	program.Uniform3f("light.color", 1.0f, 1.0f, 1.0f);

	for (Enemy &enemy : spaceInvaders.Enemies()) {
		Texture &emissionTexture = textureFactory.AK5EmissionTexture();
		Texture &diffuseTexture = textureFactory.AK5DiffuseTexture();
		Texture &specularTexture = textureFactory.BlackTexture();
		Texture &normalTexture = textureFactory.AK5NormalTexture();
		IDrawable &model = modelFactory.AK5Model();

		emissionTexture.Active(0);
		emissionTexture.Bind();

		program.Uniform1i("emissiontexture", 0);

		diffuseTexture.Active(1);
		diffuseTexture.Bind();

		program.Uniform1i("diffusetexture", 1);

		specularTexture.Active(2);
		specularTexture.Bind();

		program.Uniform1i("speculartexture", 2);

		normalTexture.Active(3);
		normalTexture.Bind();

		program.Uniform1i("normaltexture", 3);

		program.Uniform3f("material.emission", 1.0f, 1.0f, 1.0f);
		program.Uniform3f("material.ambient", 0.1f, 0.1f, 0.1f);
		program.Uniform3f("material.diffuse", 1.0f, 1.0f, 1.0f);
		program.Uniform3f("material.specular", 0.0f, 0.0f, 0.0f);
		program.Uniform1i("material.shininess", 0);
		program.Uniform1f("material.alpha", alpha);

		glm::mat4 modelMatrix = glm::translate(matrix, glm::vec3(0.0f, 0.5f, -1.0f));
		modelMatrix = glm::translate(modelMatrix, enemy.Position());

		glm::mat4 textureMatrix = glm::mat4(1.0f);

		glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
		glm::mat4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;
		glm::mat4 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelViewMatrix)));

		program.UniformMatrix4fv("NormalMatrix", 1, false, &normalMatrix[0][0]);
		program.UniformMatrix4fv("TextureMatrix", 1, false, &textureMatrix[0][0]);
		program.UniformMatrix4fv("ModelViewMatrix", 1, false, &modelViewMatrix[0][0]);
		program.UniformMatrix4fv("ModelViewProjectionMatrix", 1, false, &modelViewProjectionMatrix[0][0]);

		model.Draw();

		normalTexture.Unbind();
		specularTexture.Unbind();
		diffuseTexture.Unbind();
		emissionTexture.Unbind();
	}

	program.Stop();
}


void Scene::DrawFloor(SpaceInvaders &spaceInvaders, const glm::mat4 &matrix, float alpha) {
	IProgram &program = shaderFactory.IluminationShader();

	program.Use();

	glm::vec3 lightPosition = viewMatrix * glm::vec4(0.0f, 3.0f, -7.5f, 1.0f);

	program.Uniform3fv("light.position", 1, &lightPosition[0]);
	program.Uniform3f("light.color", 1.0f, 1.0f, 1.0f);

	Texture &emissionTexture = textureFactory.BlackTexture();
	Texture &diffuseTexture = textureFactory.SandstoneDiffuseTexture();
	Texture &specularTexture = textureFactory.SandstoneSpecularTexture();
	Texture &normalTexture = textureFactory.SandstoneNormalTexture();
	IDrawable &model = modelFactory.PlaneModel();

	emissionTexture.Active(0);
	emissionTexture.Bind();

	program.Uniform1i("emissiontexture", 0);

	diffuseTexture.Active(1);
	diffuseTexture.Bind();

	program.Uniform1i("diffusetexture", 1);

	specularTexture.Active(2);
	specularTexture.Bind();

	program.Uniform1i("speculartexture", 2);

	normalTexture.Active(3);
	normalTexture.Bind();

	program.Uniform1i("normaltexture", 3);

	program.Uniform3f("material.emission", 0.0f, 0.0f, 0.0f);
	program.Uniform3f("material.ambient", 0.1f, 0.1f, 0.1f);
	program.Uniform3f("material.diffuse", 1.0f, 1.0f, 1.0f);
	program.Uniform3f("material.specular", 1.0f, 1.0f, 1.0f);
	program.Uniform1i("material.shininess", 50);
	program.Uniform1f("material.alpha", alpha);

	glm::mat4 modelMatrix = glm::translate(matrix, glm::vec3(0.0f, 0.0f, -10.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(15.0f, 1.0f, 10.0f));

	glm::mat4 textureMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(8.0f, 8.0f, 0.0f));

	glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
	glm::mat4 modelViewProjectionMatrix = projectionMatrix * modelViewMatrix;
	glm::mat4 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelViewMatrix)));

	program.UniformMatrix4fv("NormalMatrix", 1, false, &normalMatrix[0][0]);
	program.UniformMatrix4fv("TextureMatrix", 1, false, &textureMatrix[0][0]);
	program.UniformMatrix4fv("ModelViewMatrix", 1, false, &modelViewMatrix[0][0]);
	program.UniformMatrix4fv("ModelViewProjectionMatrix", 1, false, &modelViewProjectionMatrix[0][0]);

	model.Draw();

	normalTexture.Unbind();
	specularTexture.Unbind();
	diffuseTexture.Unbind();
	emissionTexture.Unbind();

	program.Stop();
}