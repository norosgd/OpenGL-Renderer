#version 330 core

out vec4 FragColor;

in vec3 oColor;
in vec2 oTexCoord;

uniform sampler2D sTexture;

void main()
{
    FragColor = texture(sTexture, oTexCoord);
}