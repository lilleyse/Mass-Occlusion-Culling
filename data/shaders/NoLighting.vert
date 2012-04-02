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
		Outputs
---------------------------*/

layout(location = 0) out vec4 interpColor;

/*-------------------------
		Inputs
---------------------------*/
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 translation;
layout(location = 2) in vec3 normal;

/*-------------------------
		Main
---------------------------*/

void main()
{
	interpColor = vec4(normal + .3,1);
	gl_Position = ModelViewProjection.matrix * (vec4(position, 0) + translation);
}
