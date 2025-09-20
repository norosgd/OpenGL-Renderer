#version 330 core

out vec4 FragColor;

in vec2 oTexCoord;

uniform sampler2D sTexture;

void main()
{
    FragColor = texture(sTexture, oTexCoord);
}