#version 330
in  vec4 vVertex;
in  vec3 vNormal;

out vec3 vertNormal;
out vec3 lightDir;
out vec3 eyeDir;
out float vectorLength;
 
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix; 
uniform mat3 normalMatrix;
uniform vec3 lightPos;
uniform float time;
uniform sampler3D noiseTexture;

void main() {
	vertNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	vec4 eyePos = modelViewMatrix * vVertex; /// Create the eye vector 
	lightDir = normalize(lightPos - eyeDir.xyz); /// Create the light direction 
	
	eyeDir = normalize(vec3(modelViewMatrix * vVertex)); /// Create the eye vector 

	vec3 noiseVec = normalize(vec3(texture(noiseTexture, vertNormal + time * 1.5))); //Calculate the normalized perlin noise vector to point to where the vector should go

	vec3 offset = vec3(vNormal * dot(vertNormal, noiseVec) * 2.0); //Calculate how far out the noise vector should go

	float displacment = length(offset);

	vectorLength = displacment;

	gl_Position =  projectionMatrix * modelViewMatrix * (vVertex + (vec4(offset, 1.0f))); //Change the position of each vertex by the offset in the direction stored in noiseVec
}
