#pragma once

#include "config/config.h"
#include "input/input.h"
#include "renderer/renderer.h"
#include "time/time.h"

typedef struct gs {
	Renderer_State renderer;
	Config_State   config;
	Input_State    input;
	Time_State     time;
} Gs;

extern Gs gs;
