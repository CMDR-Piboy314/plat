#include "renderer.h"
#include "renderer_internal.h"

#include "../global.h"

#include <glad/glad.h>

static Renderer_State_Internal state = {0};

void renderer_init() {
	gs.renderer.width  = 800;
	gs.renderer.height = 600;
	gs.renderer.window = renderer_init_window(gs.renderer.width, gs.renderer.height);

	renderer_init_quad(&state.vao_quad, &state.vbo_quad, &state.ebo_quad);
	renderer_init_shaders(&state);
	renderer_init_colour_texture(&state.texture_colour);
}

void renderer_begin() {
	glClearColor(0.08, 0.1, 0.1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void renderer_end() {
	SDL_GL_SwapWindow(gs.renderer.window);
}

void renderer_render_quad(vec2 pos, vec2 size, vec4 colour) {
	glUseProgram(state.shader_default);

	mat4x4 model;
	mat4x4_identity(model);

	mat4x4_translate(model, pos[0], pos[1], 0);
	mat4x4_scale_aniso(model, model, size[0], size[1], 1);

	glUniformMatrix4fv(glGetUniformLocation(state.shader_default, "model"), 1, GL_FALSE, &model[0][0]);
	glUniform4fv(glGetUniformLocation(state.shader_default, "colour"), 1, colour);

	glBindVertexArray(state.vao_quad);

	glBindTexture(GL_TEXTURE_2D, state.texture_colour);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

	glBindVertexArray(0);
}

