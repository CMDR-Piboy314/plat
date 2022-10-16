#include "input.h"

#include "../global.h"
#include "../types.h"

static void update_key_state(u8 current_state, Key_State *key_state) {
	if (current_state) {
		if (*key_state > 0) {
			*key_state = KS_HELD;
		} else {
			*key_state = KS_PRESSED;
		}
	} else {
		*key_state = KS_RELEASED;
	}
}

void input_update() {
	const u8* keyboard_state = SDL_GetKeyboardState(NULL);

	update_key_state(keyboard_state[gs.config.keybinds[INPUT_KEY_LEFT]],   &gs.input.left);
	update_key_state(keyboard_state[gs.config.keybinds[INPUT_KEY_RIGHT]],  &gs.input.right);
	update_key_state(keyboard_state[gs.config.keybinds[INPUT_KEY_UP]],     &gs.input.up);
	update_key_state(keyboard_state[gs.config.keybinds[INPUT_KEY_DOWN]],   &gs.input.down);
	update_key_state(keyboard_state[gs.config.keybinds[INPUT_KEY_ESCAPE]], &gs.input.escape);
}

