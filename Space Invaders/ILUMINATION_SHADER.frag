#version 330 core

in vec3 position;
in vec3 texcoord;
in vec3 normal;
in mat3 tbn;

struct Material {
	vec3 emission;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	int shininess;
	float alpha;
};

uniform Material material;

struct Light {
	vec3 position;
	vec3 color;
};

uniform Light light;

uniform sampler2D emissiontexture;
uniform sampler2D diffusetexture;
uniform sampler2D speculartexture;
uniform sampler2D normaltexture;

out vec4 out_Color;

void main(void) {
	vec3 emission = material.emission * texture(emissiontexture, texcoord.st).rgb;

	vec3 ambient = material.ambient * light.color;
	
	vec3 n = normalize(texture(normaltexture, texcoord.st).rgb * 2.0f - 1.0f);
	vec3 l = normalize(tbn * (light.position - position));
	
	vec3 diffuse = material.diffuse * light.color * texture(diffusetexture, texcoord.st).rgb * max(dot(n, l), 0.0f);

	vec3 e = normalize(-(tbn * position));
	vec3 h = normalize(l + e);

	vec3 specular = material.specular * light.color * texture(speculartexture, texcoord.st).rgb * pow(max(dot(h, n), 0.0f), material.shininess);

	float fogcoord = gl_FragCoord.z / gl_FragCoord.w;
	
	float fogdensity = 1.0f;
	float fogfactor = (35.0f - fogcoord) / (35.0f - 8.0f);
	fogfactor = clamp(fogfactor, 0.0f, 1.0f);
	
	vec4 fogcolor = vec4(0.5f, 0.5f, 0.5f, 0.0f);
	
	out_Color = mix(fogcolor, vec4(emission + ambient + diffuse + specular, material.alpha), fogfactor);
}