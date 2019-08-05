#version 330
out vec4 FragColor;

in vec2 textureCoords;

uniform sampler2D grassTexture;

void main()
{             
    vec4 texColor = texture2D(grassTexture, textureCoords);
    if(texColor.a < 0.1)
        discard;
    FragColor = texColor;
}