#pragma once

#include <glm/mat4x4.hpp>

#include "ModelFactory.hpp"
#include "ShaderFactory.hpp"
#include "SpaceInvaders.hpp"
#include "TextureFactory.hpp"

class Scene {
	enum class CameraType {
		FIXED_OTHOGONAL,
		FIXED_PERSPECTIVE,
		FLEXIBLE_PERSPECTIVE
	};

	CameraType cameraType;

	float aspect;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	ModelFactory modelFactory;
	ShaderFactory shaderFactory;
	TextureFactory textureFactory;

public:
	Scene(void);
	Scene(const Scene &scene);
	Scene &operator=(const Scene &scene);
	~Scene(void);

public:
	void Initialize(void);
	void Reshape(int width, int height);
	void Render(SpaceInvaders &spaceInvaders);
	void Delete(void);

public:
	void FixedOrthogonal(void);
	void FixedPerspective(void);
	void FlexiblePerspective(void);
	void TogglePointLights(void);
	void ToggleSpotLight(void);
	void ToggleDirectionalLight(void);

private:
	void DrawPlayer(SpaceInvaders &spaceInvaders, const glm::mat4 &matrix, float alpha = 1.0f);
	void DrawEnemies(SpaceInvaders &spaceInvaders, const glm::mat4 &matrix, float alpha = 1.0f);
	void DrawFloor(SpaceInvaders &spaceInvaders, const glm::mat4 &matrix, float alpha = 1.0f);
};