/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2020 @claudxsm

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
extern uint8_t is_master;

#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _FN 3

enum my_keycodes { KC_CCCV = SAFE_RANGE, KC_SELCUT, KC_UNRE };
enum { TD_QUOT = 0, TD_PAGING };

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_split_3x6_3(  
    //,----------------------------------------------------.      ,----------------------------------------------.
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,           KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,       KC_BSPC,
    //|------------ +------ +-----  +---``--- +------ +------|        ------ +-----  +------ +------ +---------- +------|
        KC_LCTL,    KC_A,   KC_S,   KC_D,   LSFT_T(KC_F),   KC_G,     KC_H,   RSFT_T(KC_J),   KC_K,   KC_L,   KC_SCLN,    TD(TD_QUOT),
    //|------------ +------ +-----  +------ +------ +------|        ------ +-----  +------ +------ +---------- +------|
        KC_LSFT,    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,           KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,    KC_RSHIFT,
    //|------------ +------ +-----  +------ +------ +------|        ------ +-----  +------ +------ +---------- +------|
        KC_LALT,        MO(_LOWER),         LGUI_T(KC_SPC),         LT(_FN, KC_ENTER),   MO(_RAISE),  KC_CCCV   
    //,----------------------------------------------------.      ,----------------------------------------------.
    ),

[_LOWER] = LAYOUT_split_3x6_3(  
    //,----------------------------------------------------.      ,----------------------------------------------.
        KC_TILD,    XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, XXXXXXX,     XXXXXXX, KC_7,  KC_8,   KC_9,    KC_KP_MINUS,    _______,
    //|------------ +------ +-----  +------ +------ +------|        |------ +-----  +------ +------ +---------- +------|
        _______,    XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX,   XXXXXXX, KC_4,  KC_5,   KC_6,   KC_KP_PLUS,     XXXXXXX,
    //|------------ +------ +-----  +------ +------ +------|        |------ +-----  +------ +------ +---------- +------|
        KC_CAPS,    XXXXXXX, KC_HOME, TD(TD_PAGING), KC_END, XXXXXXX,    XXXXXXX, KC_1,  KC_2,   KC_3,  KC_DOT,        _______,
    //|------------ +------ +-----  +------ +------ +------|        |------ +-----  +------ +------ +---------- +------|
        _______,    XXXXXXX,        _______,                        _______,         KC_0,           KC_UNRE
    //,----------------------------------------------------.      ,----------------------------------------------.
    ),

[_RAISE] = LAYOUT_split_3x6_3(  
    //,----------------------------------------------------.      ,----------------------------------------------.
        KC_ESC,    KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,        KC_AMPR, KC_ASTR, KC_LCBR, KC_RCBR, KC_BSLS,    KC_DELETE,
    //|------------ +------ +-----  +------ +------ +------|        |------ +-----  +------ +------ +---------- +------|
        _______,    XXXXXXX, XXXXXXX, XXXXXXX, KC_CIRC, KC_PLUS,  KC_MINS, KC_EQL,  KC_LPRN, KC_RPRN, KC_COLON,   KC_GRV,
    //|------------ +------ +-----  +------ +------ +------|        |------ +-----  +------ +------ +---------- +------|
        _______,    XXXXXXX, XXXXXXX, KC_LABK, KC_RABK, XXXXXXX,    KC_UNDS, KC_QUES, KC_LBRC, KC_RBRC, KC_PIPE,    _______,
    //|------------ +------ +-----  +------ +------ +------|        |------ +-----  +------ +------ +---------- +------|
        _______,    XXXXXXX,        _______,                         _______,       _______,        KC_SELCUT
    //,----------------------------------------------------.      ,----------------------------------------------.
    ),

[_FN] = LAYOUT_split_3x6_3(   
    //,----------------------------------------------------.      ,----------------------------------------------.
        XXXXXXX,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,          
    //|------------ +------ +-----  +------ +------ +------|        |------ +-----  +------ +------ +---------- +------|
        _______,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_F12,                
    //|------------ +------ +-----  +------ +------ +------|        |------ +-----  +------ +------ +---------- +------|
        RESET,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_INSERT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  
    //|------------ +------ +-----  +------ +------ +------|        |------ +-----  +------ +------ +---------- +------|
        _______,      TG(_LOWER),        _______,                         _______,         XXXXXXX,      _______       
    //,----------------------------------------------------.      ,----------------------------------------------.
)
};
// clang-format on

#ifndef KEYLOGGER_LENGTH
#    define KEYLOGGER_LENGTH 1  //((int)(OLED_DISPLAY_HEIGHT / OLED_FONT_WIDTH))
#endif

static uint32_t oled_timer = 0;
static uint16_t log_timer  = 0;
static uint16_t copy_paste_timer;
static uint16_t select_cut_timer;
static uint16_t undo_redo_timer;
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {"\n"};

// clang-format off
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',  // 0X
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ', ' ',  // 4x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};
// clang-format on

qk_tap_dance_action_t tap_dance_actions[] = {[TD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DOUBLE_QUOTE), [TD_PAGING] = ACTION_TAP_DANCE_DOUBLE(KC_PGDOWN, KC_PGUP)};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifndef SPLIT_KEYBOARD
        if (keycode == RESET && !is_master) {
            return false;
            vdcs
        }
#endif
    }
    return true;
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#    ifndef SPLIT_KEYBOARD
    if (is_master) {
#    endif
        return OLED_ROTATION_270;
#    ifndef SPLIT_KEYBOARD
    } else {
        return rotation;
    }
#    endif
}

void add_keylog(uint16_t keycode) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) || (keycode >= QK_MODS && keycode <= QK_MODS_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    for (uint8_t i = (KEYLOGGER_LENGTH - 1); i > 0; --i) {
        keylog_str[i] = keylog_str[i - 1];
    }

    if (keycode < (sizeof(code_to_name) / sizeof(char))) {
        keylog_str[0] = pgm_read_byte(&code_to_name[keycode]);
    }

    log_timer = timer_read();
}

void render_keylock_status(void) {
    led_t led_state = host_keyboard_led_state();

    if (led_state.num_lock) {
        oled_write_ln_P(STR("NUM "), false);
    } else if (led_state.caps_lock) {
        oled_write_ln_P(PSTR("CAPS "), false);
    } else if (led_state.scroll_lock) {
        oled_write_ln_P(PSTR("SCR "), false);
    } else {
        oled_write_ln_P(PSTR(""), false);
    }
}

void render_keylogger_status(void) { oled_write(keylog_str, false); }

void render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR(""), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("LOWER"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("RAISE"), false);
            break;
        case _FN:
            oled_write_ln_P(PSTR("FN"), false);
            break;
        default:
            oled_write_ln_P("???", false);
    }
}

#    define OLED_RENDER_BOOTMAGIC_NAME "Boot  "
#    define OLED_RENDER_BOOTMAGIC_NKRO "NKRO"
#    define OLED_RENDER_BOOTMAGIC_NOGUI "nGUI"
#    define OLED_RENDER_BOOTMAGIC_GRV "GRV"
#    define OLED_RENDER_BOOTMAGIC_CAPS "CAPS"

void render_bootmagic_status(void) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };

    bool is_bootmagic_on;
#    ifdef OLED_DISPLAY_128X64
    is_bootmagic_on = !keymap_config.swap_lctl_lgui;
#    else
    is_bootmagic_on = keymap_config.swap_lctl_lgui;
#    endif

    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NAME), false);
#    ifdef OLED_DISPLAY_128X64
    if (keymap_config.swap_lctl_lgui)
#    else
    oled_write_P(PSTR(" "), false);
#    endif
    {
        oled_write_P(logo[1][0], is_bootmagic_on);
#    ifdef OLED_DISPLAY_128X64
    } else {
#    endif
        oled_write_P(logo[0][0], !is_bootmagic_on);
    }
    oled_write_P(PSTR(" "), false);
#    ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NKRO), keymap_config.nkro);
    oled_write_P(PSTR(" "), false);
    oled_write_ln_P(PSTR(OLED_RENDER_BOOTMAGIC_NOGUI), !keymap_config.no_gui);
    oled_write_P(PSTR("Magic "), false);
    if (keymap_config.swap_lctl_lgui)
#    endif
    {
        oled_write_P(logo[1][1], is_bootmagic_on);
#    ifdef OLED_DISPLAY_128X64
    } else {
#    endif
        oled_write_P(logo[0][1], !is_bootmagic_on);
    }
    oled_write_P(PSTR(" "), false);
#    ifdef OLED_DISPLAY_128X64
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_GRV), keymap_config.swap_grave_esc);
    oled_write_P(PSTR("  "), false);
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_CAPS), keymap_config.swap_control_capslock);
    oled_advance_page(true);
#    else
    oled_write_P(PSTR(OLED_RENDER_BOOTMAGIC_NKRO), keymap_config.nkro);
#    endif
}

void render_status_main(void) {
    /* Show Keyboard Layout  */
    // oled_write_P(PSTR("TEST XXX"), false);

    // don't care render_default_layer_state();
    render_layer_state();
    oled_write_ln_P(PSTR(""), false);
    render_keylock_status();
    // render_bootmagic_status();

    oled_write_ln_P(PSTR(""), false);
    // don't care render_user_status();

    render_keylogger_status();
    oled_write_ln_P(PSTR(""), false);
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};
    oled_write_P(crkbd_logo, false);

    // clang-format off
    //static const char PROGMEM qmk_logo[] = {
        // 0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        // 0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        // 0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
    // clang-format on
    // oled_write_P(qmk_logo, false);
}

void render_status_secondary(void) { oled_render_logo(); }

void update_log(void) {
    if (timer_elapsed(log_timer) > 750) {
        // add_keylog(0);
    }
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 300000) {
        oled_off();
        return;
    }
#    ifndef SPLIT_KEYBOARD
    else {
        oled_on();
    }
#    endif
    update_log();

    if (is_master) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

bool process_record_user_oled(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        oled_timer = timer_read32();
        add_keylog(keycode);
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#    ifdef OLED_DRIVER_ENABLE
    process_record_user_oled(keycode, record);
#    endif

    switch (keycode) {
        case KC_CCCV:  // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                    tap_code16(LGUI(KC_C));
                } else {
                    tap_code16(LGUI(KC_V));  // Tap, paste
                }
            }
            break;
        case KC_SELCUT:
            if (record->event.pressed) {
                select_cut_timer = timer_read();
            } else {
                if (timer_elapsed(select_cut_timer) > TAPPING_TERM) {  // Hold, cut
                    tap_code16(LGUI(KC_X));
                } else {
                    tap_code16(LGUI(KC_A));  // Tap, select all
                }
            }
            break;
        case KC_UNRE:
            if (record->event.pressed) {
                undo_redo_timer = timer_read();
            } else {
                if (timer_elapsed(undo_redo_timer) > TAPPING_TERM) {  // Hold, redo
                    tap_code16(SGUI(KC_Z));
                } else {
                    tap_code16(LGUI(KC_Z));  // Tap, undo
                }
            }
            break;
    }
    return true;
}

#endif  // OLED_DRIVER_ENABLE

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_F):
        case RSFT_T(KC_J):
            return 150;  // was 200
        case LGUI_T(KC_SPC):
        case LT(_FN, KC_ENTER):
            return TAPPING_TERM + 300;
        // case SFT_T(KC_SPC):
        //    return TAPPING_TERM + 1250;
        // case LT(1, KC_GRV):
        //    return 130;
        default:
            return TAPPING_TERM;
    }
}