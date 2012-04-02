#version 420 core

layout (location = 0, index = 0) out vec4 fragColor;

layout(location = 0) in vec4 interpColor;

void main()
{

	fragColor = interpColor;
}
