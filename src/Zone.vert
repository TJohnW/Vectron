#version 120

in vec2 vert;

uniform mat4 MVP;

void main() {
	gl_Position = MVP * vec4( vert, 0, 1 );
}