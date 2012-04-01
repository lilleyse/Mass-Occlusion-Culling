#version 420 core

layout(binding = 0, offset = 0) uniform atomic_uint instanceCounter;

/*-------------------------
		Uniforms
---------------------------*/

layout(binding = 0) uniform transform
{
	mat4 matrix;
} ModelViewProjection;

/*-------------------------
		Inputs
---------------------------*/
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 translation;

/*-------------------------
		Main
---------------------------*/

void main()
{
	gl_Position = ModelViewProjection.matrix * vec4(position + translation, 1);
}
