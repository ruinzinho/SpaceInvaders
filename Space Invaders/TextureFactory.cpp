#include "TextureFactory.hpp"

#include <gl/glew.h>

#include <gli/gl.hpp>
#include <gli/load.hpp>

#include <glm/vec3.hpp>

#include "Log.hpp"


TextureFactory::TextureFactory(void) {
}


TextureFactory::TextureFactory(const TextureFactory &textureFactory) {
	textures2D = textureFactory.textures2D;
}


TextureFactory &TextureFactory::operator=(const TextureFactory &textureFactory) {
	textures2D = textureFactory.textures2D;

	return *this;
}


TextureFactory::~TextureFactory(void) {
}


void TextureFactory::Initialize(void) {
	Texture2D &ak5Diffuse = CreateTexture2DFromFile("AK_5_DIFFUSE_TEXTURE.dds");
	Texture2D &ak5Emission = CreateTexture2DFromFile("AK_5_EMISSION_TEXTURE.dds");
	Texture2D &ak5Normal = CreateTexture2DFromFile("AK_5_NORMAL_TEXTURE.dds");

	textures2D["AK_5_DIFFUSE_TEXTURE"] = ak5Diffuse;
	textures2D["AK_5_EMISSION_TEXTURE"] = ak5Emission;
	textures2D["AK_5_NORMAL_TEXTURE"] = ak5Normal;

	Texture2D &arc170Diffuse = CreateTexture2DFromFile("ARC_170_DIFFUSE_TEXTURE.dds");
	Texture2D &arc170Normal = CreateTexture2DFromFile("ARC_170_NORMAL_TEXTURE.dds");
	Texture2D &arc170Specular = CreateTexture2DFromFile("ARC_170_SPECULAR_TEXTURE.dds");

	textures2D["ARC_170_DIFFUSE_TEXTURE"] = arc170Diffuse;
	textures2D["ARC_170_NORMAL_TEXTURE"] = arc170Normal;
	textures2D["ARC_170_SPECULAR_TEXTURE"] = arc170Specular;

	Texture2D &sandstoneDiffuse = CreateTexture2DFromFile("SANDSTONE_DIFFUSE_TEXTURE.dds");
	Texture2D &sandstoneNormal = CreateTexture2DFromFile("SANDSTONE_NORMAL_TEXTURE.dds");
	Texture2D &sandstoneSpecular = CreateTexture2DFromFile("SANDSTONE_SPECULAR_TEXTURE.dds");

	textures2D["SANDSTONE_DIFFUSE_TEXTURE"] = sandstoneDiffuse;
	textures2D["SANDSTONE_NORMAL_TEXTURE"] = sandstoneNormal;
	textures2D["SANDSTONE_SPECULAR_TEXTURE"] = sandstoneSpecular;

	Texture2D &white = CreateTexture2DFromFile("WHITE_TEXTURE.dds");
	Texture2D &black = CreateTexture2DFromFile("BLACK_TEXTURE.dds");
	Texture2D &blankNormal = CreateTexture2DFromFile("BLANK_NORMAL_TEXTURE.dds");

	textures2D["WHITE_TEXTURE"] = white;
	textures2D["BLACK_TEXTURE"] = black;
	textures2D["BLANK_NORMAL_TEXTURE"] = blankNormal;
}


Texture &TextureFactory::AK5DiffuseTexture(void) {
	return textures2D["AK_5_DIFFUSE_TEXTURE"];
}


Texture &TextureFactory::AK5EmissionTexture(void) {
	return textures2D["AK_5_EMISSION_TEXTURE"];
}


Texture &TextureFactory::AK5NormalTexture(void) {
	return textures2D["AK_5_NORMAL_TEXTURE"];
}


Texture &TextureFactory::ARC170DiffuseTexture(void) {
	return textures2D["ARC_170_DIFFUSE_TEXTURE"];
}


Texture &TextureFactory::ARC170NormalTexture(void) {
	return textures2D["ARC_170_NORMAL_TEXTURE"];
}


Texture &TextureFactory::ARC170SpecularTexture(void) {
	return textures2D["ARC_170_SPECULAR_TEXTURE"];
}


Texture &TextureFactory::SandstoneDiffuseTexture(void) {
	return textures2D["SANDSTONE_DIFFUSE_TEXTURE"];
}


Texture &TextureFactory::SandstoneNormalTexture(void) {
	return textures2D["SANDSTONE_NORMAL_TEXTURE"];
}


Texture &TextureFactory::SandstoneSpecularTexture(void) {
	return textures2D["SANDSTONE_SPECULAR_TEXTURE"];
}


Texture &TextureFactory::WhiteTexture(void) {
	return textures2D["WHITE_TEXTURE"];
}


Texture &TextureFactory::BlackTexture(void) {
	return textures2D["BLACK_TEXTURE"];
}


Texture &TextureFactory::BlankNormalTexture(void) {
	return textures2D["BLANK_NORMAL_TEXTURE"];
}


void TextureFactory::Delete(void) {
	for (std::pair<const std::string, Texture2D> &keyValue : textures2D) {
		Texture2D &texture2D = keyValue.second;
		texture2D.Delete();
	}
}


unsigned int TextureFactory::ReadFromFile(const std::string &filename) {
	gli::texture texture = gli::load(filename);

	if (texture.empty()) {
		Log::Error("Couldn't open " + filename);
		exit(EXIT_FAILURE);
	}

	Log::Loading(filename);

	gli::gl gl(gli::gl::PROFILE_GL33);
	const gli::gl::format format = gl.translate(texture.format(), texture.swizzles());
	GLenum target = gl.translate(texture.target());

	unsigned int id;

	glGenTextures(1, &id);
	glBindTexture(target, id);

	glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(texture.levels() - 1));
	glTexParameteri(target, GL_TEXTURE_SWIZZLE_R, format.Swizzles[0]);
	glTexParameteri(target, GL_TEXTURE_SWIZZLE_G, format.Swizzles[1]);
	glTexParameteri(target, GL_TEXTURE_SWIZZLE_B, format.Swizzles[2]);
	glTexParameteri(target, GL_TEXTURE_SWIZZLE_A, format.Swizzles[3]);

	const glm::tvec3<GLsizei> extent(texture.extent());
	const GLsizei faceTotal = static_cast<GLsizei>(texture.layers() * texture.faces());

	switch (texture.target()) {
	case gli::TARGET_1D:
		glTexStorage1D(
			target, static_cast<GLsizei>(texture.levels()), format.Internal, extent.x);
		break;
	case gli::TARGET_1D_ARRAY:
	case gli::TARGET_2D:
	case gli::TARGET_CUBE:
		glTexStorage2D(
			target, static_cast<GLsizei>(texture.levels()), format.Internal,
			extent.x, texture.target() == gli::TARGET_2D ? extent.y : faceTotal);
		break;
	case gli::TARGET_2D_ARRAY:
	case gli::TARGET_3D:
	case gli::TARGET_CUBE_ARRAY:
		glTexStorage3D(
			target, static_cast<GLsizei>(texture.levels()), format.Internal,
			extent.x, extent.y,
			texture.target() == gli::TARGET_3D ? extent.z : faceTotal);
		break;
	}

	for (size_t layer = 0; layer < texture.layers(); layer++) {
		for (size_t face = 0; face < texture.faces(); face++) {
			for (size_t level = 0; level < texture.levels(); level++) {
				const GLsizei layerGL = static_cast<GLsizei>(layer);
				glm::tvec3<GLsizei> extent(texture.extent(level));
				target = gli::is_target_cube(texture.target())
					? static_cast<GLenum>(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face)
					: target;

				switch (texture.target()) {
				case gli::TARGET_1D:
					if (gli::is_compressed(texture.format())) {
						glCompressedTexSubImage1D(
							target, static_cast<GLint>(level), 0, extent.x,
							format.Internal, static_cast<GLsizei>(texture.size(level)),
							texture.data(layer, face, level));
					}
					else {
						glTexSubImage1D(
							target, static_cast<GLint>(level), 0, extent.x,
							format.External, format.Type,
							texture.data(layer, face, level));
					}
					break;
				case gli::TARGET_1D_ARRAY:
				case gli::TARGET_2D:
				case gli::TARGET_CUBE:
					if (gli::is_compressed(texture.format())) {
						glCompressedTexSubImage2D(
							target, static_cast<GLint>(level),
							0, 0,
							extent.x,
							texture.target() == gli::TARGET_1D_ARRAY ? layerGL : extent.y,
							format.Internal, static_cast<GLsizei>(texture.size(level)),
							texture.data(layer, face, level));
					}
					else {
						glTexSubImage2D(
							target, static_cast<GLint>(level),
							0, 0,
							extent.x,
							texture.target() == gli::TARGET_1D_ARRAY ? layerGL : extent.y,
							format.External, format.Type,
							texture.data(layer, face, level));
					}
					break;
				case gli::TARGET_2D_ARRAY:
				case gli::TARGET_3D:
				case gli::TARGET_CUBE_ARRAY:
					if (gli::is_compressed(texture.format())) {
						glCompressedTexSubImage3D(
							target, static_cast<GLint>(level),
							0, 0, 0,
							extent.x, extent.y,
							texture.target() == gli::TARGET_3D ? extent.z : layerGL,
							format.Internal, static_cast<GLsizei>(texture.size(level)),
							texture.data(layer, face, level));
					}
					else {
						glTexSubImage3D(
							target, static_cast<GLint>(level),
							0, 0, 0,
							extent.x, extent.y,
							texture.target() == gli::TARGET_3D ? extent.z : layerGL,
							format.External, format.Type,
							texture.data(layer, face, level));
					}
					break;
				}
			}
		}
	}

	glBindTexture(target, 0);

	return id;
}


Texture2D TextureFactory::CreateTexture2DFromFile(const std::string &filename) {
	Texture2D texture2D;
	texture2D.Id(ReadFromFile(filename));

	return texture2D;
}