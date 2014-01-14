#version 150

out vec2 tx;

in vec3 in_Position;
in vec2 in_TexCoord;

layout(std140) uniform GlobalMatrices
{
	mat4 Projection;
	mat4 View;
};

void main()
{
	vec4 vrcPos = View * vec4(in_Position,1);
	gl_Position = Projection * vrcPos;
	
	tx = in_TexCoord;
}
