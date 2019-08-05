#version 330

in  vec3 vertNormal;
in  vec3 lightDir;
in  vec3 eyeDir;
in  float vectorLength;

out vec4 fragColor;

uniform mat4 modelViewMatrix; 
uniform samplerCube cubeTexture;
uniform float time;
uniform sampler3D noiseTexture;


void main() {
	//fragColor = mix(texture(cubeTexture, vec3(1.0, 0.0, 0.0)), texture(cubeTexture, vec3(0.0, 0.0, 0.0)), length);

	if(length > 0 && length < 0.5){
		fragColor = texture(cubeTexture, vec3(1.0, 0.0, 0.0));
	}
	else{
		fragColor = texture(cubeTexture, vec3(0.0, 0.0, 0.0));
	}
} 