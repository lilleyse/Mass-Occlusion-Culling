#version 420 core

#define POSITION		0

/*-------------------------
		Inputs
---------------------------*/
layout(location = POSITION) in vec4 position;

/*-------------------------
		Outputs
---------------------------*/

out gl_PerVertex
{
	vec4 gl_Position;
};

/*-------------------------
		Main
---------------------------*/

void main()
{
	gl_Position = position;
}
