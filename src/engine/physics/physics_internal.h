#pragma once

#include "../array_list/array_list.h"
#include "../types.h"

typedef struct physics_state_internal {
	Array_List* body_list;
} Physics_State_Internal;

Physics_State_Internal state;

