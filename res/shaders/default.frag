#version 330 core

out vec4 frag_colour;

in vec2 uvs;

uniform vec4 colour;
uniform sampler2D texture_id;

void main() {
	frag_colour = texture(texture_id, uvs) * colour;
}
