#version 330 core

in vec3 in_Position;
in vec3 in_Texcoord;
in vec3 in_Normal;
in vec3 in_Tangent;

uniform mat4 NormalMatrix;
uniform mat4 TextureMatrix;
uniform mat4 ModelViewMatrix;
uniform mat4 ModelViewProjectionMatrix;

out vec3 position;
out vec3 texcoord;
out vec3 normal;
out mat3 tbn;

void main(void) {
	position = vec3(ModelViewMatrix * vec4(in_Position, 1.0f));
	texcoord = vec3(TextureMatrix * vec4(in_Texcoord, 1.0f));
	normal = vec3(NormalMatrix * vec4(in_Normal, 0.0f));
	
	vec3 T = normalize(in_Tangent);
	vec3 N = normalize(normal);
	vec3 B = cross(T, N);
	
	tbn = transpose(mat3(T, B, N));

	gl_Position = ModelViewProjectionMatrix * vec4(in_Position, 1.0f);
}