#pragma once

#include "renderer.h"

#include "../types.h"

#include <SDL2/SDL.h>

typedef struct renderer_state_internal {
	u32 vao_quad;
	u32 vbo_quad;
	u32 ebo_quad;

	u32 shader_default;
	u32 texture_colour;

	mat4x4 proj;
} Renderer_State_Internal;

SDL_Window* renderer_init_window(u32 width, u32 height);

void renderer_init_quad(u32* vao, u32* vbo, u32* ebo);
void renderer_init_colour_texture(u32* texture);
void renderer_init_shaders(Renderer_State_Internal* state);

u32 renderer_shader_create(const char* vert_path, const char* frag_path);
