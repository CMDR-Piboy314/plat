#pragma once

#include "../types.h"

#include <linmath.h>


typedef struct aabb {
	vec2 pos;
	vec2 half_size;
} AABB;

typedef struct body {
	AABB aabb;

	vec2 vel;
	vec2 accel;
} Body;

void physics_init();
void physics_update();

size_t physics_body_create(vec2 pos, vec2 size);
Body*  physics_body_get(size_t index);

