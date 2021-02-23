#version 450

uniform sampler2D defaultTexture;

in vec2 UVs;

out vec4 FragColour;

void main()
{
	FragColour = vec4(texture(defaultTexture, UVs).rgb, 1.0);
}