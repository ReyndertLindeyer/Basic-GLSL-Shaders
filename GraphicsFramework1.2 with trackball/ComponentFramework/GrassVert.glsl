#version 330


in  vec4 vVertex;
in  vec4 vNormal;
in  vec2 vTexture;
in  vec3 vPosition;


out vec3 vertNormal;
out vec3 lightDir;

out vec2 textureCoords;

out vec3 eyeDir;
 
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix; 
uniform mat3 normalMatrix;
uniform vec3 lightPos;
uniform sampler2D grassTexture;
uniform vec3 vClusterTranslation;

void main() {
	textureCoords = vTexture;
	float fObjectHeight = 1;
	vec3 tempPosition = vec3 (1,1,1);
	
	if (textureCoords.x <= 0.1) { //I am unsure entirly why this is x instead of y, but I am fairly certain it is because of the way I made the model/its orientation
    
		// A N I M A T I O N  (to world space)
		tempPosition = vPosition.xyz + vClusterTranslation;
		
		//vec3 tempNormal = normalize(vNormal * fObjectHeight + vClusterTranslation);

	}
	vertNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	vec4 eyePos = modelViewMatrix * vVertex; /// Create the eye vector 
	lightDir = normalize(lightPos - eyeDir.xyz); /// Create the light direction 

	
	eyeDir = normalize(vec3(modelViewMatrix * vVertex)); /// Create the eye vector 

	gl_Position =  projectionMatrix * modelViewMatrix * vVertex * vec4(tempPosition, 1); 
}
