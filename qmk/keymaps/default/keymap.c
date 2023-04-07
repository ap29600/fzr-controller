// Copyright 2023 Andrea Piseri
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Only 4 of these are actually used, axes 3 and 4 (right stick) are always 0.
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
	JOYSTICK_AXIS_VIRTUAL,
	JOYSTICK_AXIS_VIRTUAL,
	JOYSTICK_AXIS_VIRTUAL,
	JOYSTICK_AXIS_VIRTUAL,
	JOYSTICK_AXIS_VIRTUAL,
	JOYSTICK_AXIS_VIRTUAL,
};

enum custom_keycodes {
	GP_DPU = SAFE_RANGE,
	GP_DPD,
	GP_DPL,
	GP_DPR,
	GP_LT,
	GP_RT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_hitbox(
		JS_2,    JS_3,    JS_5,    JS_4,
		JS_0,    JS_1,    GP_RT,   GP_LT,
		GP_DPL,  GP_DPD,  GP_DPR,  GP_DPU,  JS_7
    )
};

int16_t GP_DPU_STATE = 0;
int16_t GP_DPD_STATE = 0;
int16_t GP_DPL_STATE = 0;
int16_t GP_DPR_STATE = 0;

bool process_record_user (uint16_t keycode, keyrecord_t *record) {
	switch(keycode) {
		case GP_DPU:
			GP_DPU_STATE = record->event.pressed;
			joystick_set_axis(1, (int16_t)127 * (GP_DPD_STATE - GP_DPU_STATE));
			return false;
		case GP_DPD:
			GP_DPD_STATE = record->event.pressed;
			joystick_set_axis(1, (int16_t)127 * (GP_DPD_STATE - GP_DPU_STATE));
			return false;
		case GP_DPL:
			GP_DPL_STATE = record->event.pressed;
			joystick_set_axis(0, (int16_t)127 * (GP_DPR_STATE - GP_DPL_STATE));
			return false;
		case GP_DPR:
			GP_DPR_STATE = record->event.pressed;
			joystick_set_axis(0, (int16_t)127 * (GP_DPR_STATE - GP_DPL_STATE));
			return false;
		case GP_LT:
			joystick_set_axis(2, -127 + 254 * record->event.pressed);
			return false;
		case GP_RT:
			joystick_set_axis(5, -127 + 254 * record->event.pressed);
			return false;
		default:
			return true;
	}
}

void keyboard_post_init_user() {
	joystick_set_axis(2, -127); // LT
	joystick_set_axis(5, -127); // RT
}
