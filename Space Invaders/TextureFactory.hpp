#pragma once

#include <string>
#include <map>

#include "Texture.hpp"
#include "Texture2D.hpp"

class TextureFactory {
	std::map<std::string, Texture2D> textures2D;

public:
	TextureFactory(void);
	TextureFactory(const TextureFactory &textureFactory);
	TextureFactory &operator=(const TextureFactory &textureFactory);
	~TextureFactory(void);

public:
	void Initialize(void);

public:
	Texture &AK5DiffuseTexture(void);
	Texture &AK5EmissionTexture(void);
	Texture &AK5NormalTexture(void);

	Texture &ARC170DiffuseTexture(void);
	Texture &ARC170NormalTexture(void);
	Texture &ARC170SpecularTexture(void);

	Texture &SandstoneDiffuseTexture(void);
	Texture &SandstoneNormalTexture(void);
	Texture &SandstoneSpecularTexture(void);

	Texture &WhiteTexture(void);
	Texture &BlackTexture(void);
	Texture &BlankNormalTexture(void);
	Texture &SpaceInvadersLogoTexture(void);

public:
	void Delete(void);

private:
	unsigned int ReadFromFile(const std::string &filename);
	Texture2D CreateTexture2DFromFile(const std::string &filename);
};