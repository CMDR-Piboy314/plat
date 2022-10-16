#include <stdio.h>
#include <stdbool.h>
#include <glad/glad.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "engine/config/config.h"
#include "engine/input/input.h"
#include "engine/physics/physics.h"
#include "engine/time/time.h"
#include "engine/global.h"

static bool should_quit = false;
static vec2 pos;

static void handle_input() {
	if (gs.input.left == KS_PRESSED || gs.input.left == KS_HELD) {
		pos[0] -= 500 * gs.time.dt;
	} if (gs.input.right == KS_PRESSED || gs.input.right == KS_HELD) {
		pos[0] += 500 * gs.time.dt;
	} if (gs.input.up == KS_PRESSED || gs.input.up == KS_HELD) {
		pos[1] += 500 * gs.time.dt;
	} if (gs.input.down == KS_PRESSED || gs.input.down == KS_HELD) {
		pos[1] -= 500 * gs.time.dt;
	}

	if (gs.input.escape == KS_PRESSED || gs.input.escape == KS_HELD) {
		should_quit = true;
	}
}

int main(int argc, char* argv[]) {
	time_init(60);
	config_init();
	renderer_init();
	physics_init();

	u32 body_count = 100;

	for (u32 i = 0; i < body_count; ++i) {
		size_t body_index = physics_body_create(
				(vec2){rand() % (i32)gs.renderer.width, rand() % (i32)gs.renderer.height},
				(vec2){rand() % 100, rand() % 100}
		);

		Body* body = physics_body_get(body_index);

		body->accel[0] = rand() % 200 - 100;
		body->accel[1] = rand() % 200 - 100;
	}

	pos[0] = gs.renderer.width  / 2;
	pos[1] = gs.renderer.height / 2;

	while (should_quit == false) {
		/* TODO: Move this */
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					should_quit = true;
					break;
				default:
					break;
			}
		}

		time_update();
		input_update();
		physics_update();

		handle_input();

		renderer_begin();

		for (u32 i = 0; i < body_count; ++i) {
			Body* body = physics_body_get(i);

			renderer_render_quad(body->aabb.pos, body->aabb.half_size, (vec4){0, 0, 1, 1});

			if (body->aabb.pos[0] > gs.renderer.width || body->aabb.pos[0] < 0) {
				body->vel[0] *= -1;
			} if (body->aabb.pos[1] > gs.renderer.height || body->aabb.pos[1] < 0) {
				body->vel[1] *= -1;
			}

			if (body->vel[0] > 500) {
				body->vel[0] = 500;
			} if (body->vel[0] < -500) {
				body->vel[0] = -500;
			} if (body->vel[1] > 500) {
				body->vel[1] = 500;
			} if (body->vel[1] < -500) {
				body->vel[1] = -500;
			}
		}

		renderer_render_quad(pos, (vec2){50, 50}, (vec4){0, 1, 0, 1});

		renderer_end();
	}

	return 0;
}
