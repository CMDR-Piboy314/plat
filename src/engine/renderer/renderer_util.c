#include "renderer_internal.h"

#include "../util.h"
#include "../io/io.h"

#include <glad/glad.h>
#include <stdio.h>

u32 renderer_shader_create(const char* vert_path, const char* frag_path) {
	int success;
	char log[512];

	File vert_file = io_file_read(vert_path);

	if (!vert_file.is_valid) {
		ERROR_EXIT("Error reading shader %s\n", vert_path);
	}

	u32 vert_shader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vert_shader, 1, (const char* const*)&vert_file, NULL);
	glCompileShader(vert_shader);

	glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vert_shader, 512, NULL, log);

		ERROR_EXIT("Error compiling vertex shader %s\n", log);
	}

	File frag_file = io_file_read(frag_path);

	if (!frag_file.is_valid) {
		ERROR_EXIT("Error reading shader %s\n", frag_path);
	}

	u32 frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(frag_shader, 1, (const char* const*)&frag_file, NULL);
	glCompileShader(frag_shader);

	glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(frag_shader, 512, NULL, log);

		ERROR_EXIT("Error compiling fragment shader %s\n", log);
	}

	u32 shader = glCreateProgram();

	glAttachShader(shader, vert_shader);
	glAttachShader(shader, frag_shader);

	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shader, 512, NULL, log);

		ERROR_EXIT("Error linking shader %s\n", log);
	}

	free(vert_file.data);
	free(frag_file.data);


	return shader;
}
