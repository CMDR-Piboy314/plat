#pragma once

typedef enum input_keys {
	INPUT_KEY_LEFT;
	INPUT_KEY_RIGHT,
	INPUT_KEY_UP,
	INPUT_KEY_DOWN,
	INPUT_KEY_ESCAPE
} Input_Keys;

typedef struct input_state {
	Key_State left;
	Key_State right;
	Key_State up;
	Key_State down;
	Key_State escape;
} Input_State;

typedef enum key_state {
	KS_RELEASED,
	KS_PRESSED,
	KS_HELD
} Key_State;

void input_update();

