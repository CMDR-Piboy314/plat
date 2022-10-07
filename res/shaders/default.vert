#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 0) in vec3 a_uvs;

out vec2 uvs;

uniform mat4 proj;
uniform mat4 model;

void main() {
	uvs = a_uvs;

	gl_Position = proj * model * vec4(a_pos, 1.0);
}
