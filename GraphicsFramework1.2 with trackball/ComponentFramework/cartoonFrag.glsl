#version 330

in  vec3 vertNormal;
in  vec3 lightDir;
in  vec3 eyeDir;
out vec4 fragColor;


void main() { 
	/// I could have passed these in as Uniforms but for simplicity, 
	/// I'll just define them here: specular, diffuse, ambient for the surface material 
	//const vec4 ks = vec4(0.5, 0.3, 0.3, 0.0);

	//Commented out to get textures working
	//const vec4 kd = vec4(0.6, 0.8, 0.6, 0.0); /// const means it cannot be changed just like C++
	//const vec4 ka = 0.1 * kd;

	//vec3 halfDir = normalize(lightDir + viewDir);
    //float specAngle = max(dot(halfDir, vertNormal), 0.0);
    //float spec = pow(specAngle, 16.0);

	//float diff = max(dot(vertNormal, lightDir), 0.0);

	fragColor = mix(vec4(0.0, 0.0, 0.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0), dot(-eyeDir, vertNormal));

	//fragColor =  ka + (diff * kd) + (spec * ks);
	
} 

