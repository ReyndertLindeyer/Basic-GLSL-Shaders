#version 330

in  vec3 vertNormal;
in  vec3 lightDir;
in  vec3 eyeDir;

out vec4 fragColor;

uniform mat4 modelViewMatrix; 
uniform samplerCube cubeTexture;
uniform float time;


void main() { 
	mat3 scale = mat3(vec3(-1.0,0.0,0.0),
					  vec3(0.0,1.0,0.0),
					  vec3(0.0,0.0,1.0));
	vec3 reflection = reflect(eyeDir, vertNormal);
	vec3 refraction = refract (eyeDir, vertNormal, 1.0/1.6);
	reflection = vec3 (inverse (modelViewMatrix) * vec4 (reflection, 0.0));
	refraction = vec3 (inverse (modelViewMatrix) * vec4 (refraction, 0.0));

	vec3 mixedRs = mix(reflection, refraction,  dot(vertNormal, -eyeDir));

	fragColor =  texture(cubeTexture, scale * mixedRs);
} 