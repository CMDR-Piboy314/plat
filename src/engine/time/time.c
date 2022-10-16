#include "time.h"

#include "../global.h"

#include <SDL2/SDL.h>

void time_init(u32 frame_rate) {
	gs.time.frame_rate = frame_rate;
	gs.time.frame_delay = 100.f / frame_rate;
}

void time_update() {
	gs.time.now  = (f32)SDL_GetTicks();
	gs.time.dt   = (gs.time.now - gs.time.last) / 1000.f;
	gs.time.last =  gs.time.now;

	++gs.time.frame_count;

	if (gs.time.now - gs.time.frame_last >= 1000.f) {
		gs.time.frame_rate = gs.time.frame_count;
		gs.time.frame_count = 0;
		gs.time.frame_last = gs.time.now;
	}
}

void time_update_late() {
	gs.time.frame_time = (f32)SDL_GetTicks() - gs.time.now;

	if (gs.time.frame_delay > gs.time.frame_time) {
		SDL_Delay(gs.time.frame_delay - gs.time.frame_time);
	}
}

