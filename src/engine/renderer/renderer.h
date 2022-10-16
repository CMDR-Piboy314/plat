#pragma once

#include "../types.h"

#include <SDL2/SDL.h>
#include <linmath.h>

typedef struct renderer_state {
	SDL_Window* window;

	i32 width;
	i32 height;
} Renderer_State;

void renderer_init();
void renderer_begin();
void renderer_end();

void renderer_render_quad(vec2 pos, vec2 size, vec4 colour);
