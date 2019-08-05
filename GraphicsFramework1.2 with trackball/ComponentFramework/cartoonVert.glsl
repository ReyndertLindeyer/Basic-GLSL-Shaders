#version 330
in  vec4 vVertex;
in  vec4 vNormal;

out vec3 vertNormal;
out vec3 lightDir;

out vec3 eyeDir;
 
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix; 
uniform mat3 normalMatrix;
uniform vec3 lightPos;

void main() {
	vertNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	vec4 eyePos = modelViewMatrix * vVertex; /// Create the eye vector 
	lightDir = normalize(lightPos - eyeDir.xyz); /// Create the light direction 
	
	eyeDir = normalize(vec3(modelViewMatrix * vVertex)); /// Create the eye vector 

	gl_Position =  projectionMatrix * modelViewMatrix * vVertex; 
}
