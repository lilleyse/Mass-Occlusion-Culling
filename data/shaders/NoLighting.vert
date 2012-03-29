#version 420 core


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
layout(location = 0) in vec4 position;

/*-------------------------
		Outputs
---------------------------*/

out gl_PerVertex
{
	vec4 gl_Position;
	float gl_PointSize;
	float gl_ClipDistance[];
};



/*-------------------------
		Main
---------------------------*/

void main()
{
	gl_Position = ModelViewProjection.matrix * position;
}
