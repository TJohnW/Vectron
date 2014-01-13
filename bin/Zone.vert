#version 130

in vec2 vert;

uniform mat4 MVP;

void main() {
	gl_Position = vec4( vert.x, vert.y, 0, 1 );
}