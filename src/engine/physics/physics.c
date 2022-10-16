#include "physics.h"

#include "physics_internal.h"

#include "../array_list/array_list.h"
#include "../global.h"
#include "../util.h"

#include <linmath.h>


void physics_init() {
	state.body_list = array_list_create(sizeof(Body), 0);
}

void physics_update() {
	Body* body;

	for (u32 i = 0; i < state.body_list->len; ++i) {
		body = array_list_get(state.body_list, i);

		body->vel[0]      += body->accel[0] * gs.time.dt;
		body->vel[1]      += body->accel[1] * gs.time.dt;

		body->aabb.pos[0] += body->vel[0]   * gs.time.dt;
		body->aabb.pos[1] += body->vel[1]   * gs.time.dt;
	}
}


size_t physics_body_create(vec2 pos, vec2 size) {
	Body body = {
		.aabb = {
			.pos = {pos[0], pos[1]},
			.half_size = {size[0] / 2, size[1] / 2},
		},

		.vel = {0, 0},
	};

	if (array_list_append(state.body_list, &body) == (size_t)-1) {
		ERROR_EXIT("Failed to append body to list!\n");
	}

	return state.body_list->len - 1;
}

Body*  physics_body_get(size_t index) {
	return array_list_get(state.body_list, index);
}

