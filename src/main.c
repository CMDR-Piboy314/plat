#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "engine/global.h"

int main(int argc, char* argv[]) {
	renderer_init();

	bool should_quit = false;

	while(!should_quit) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					should_quit = true;
					break;
				default:
					break;
			}
		}

		renderer_begin();

		renderer_render_quad((vec2){gs.renderer.width * 0.5, gs.renderer.height * 0.5}, (vec2){50, 50}, (vec4){1, 1, 0, 1});

		renderer_end();
	}

	return 0;
}
