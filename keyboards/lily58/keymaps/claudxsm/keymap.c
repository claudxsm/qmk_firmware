/* Attribution-ShareAlike 4.0 International (CC BY-SA 4.0) 2020 Max Drasbeck 
 *
 * You are free to:
 *
 *  Share — copy and redistribute the material in any medium or format
 *  Adapt — remix, transform, and build upon the material
 *   for any purpose, even commercially.
 *
 * The licensor cannot revoke these freedoms as long as you follow the license terms.
 */

#include QMK_KEYBOARD_H
extern uint8_t is_master;

enum layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _FN,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  FN,
  KC_CCCV, KC_SELCUT, KC_UNRE 
};
enum { TD_QUOT = 0 };


//  The press-action of the encoder is controlled by the switch that it replaces - simply change what it does in the regular keymap area.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_LGUI, KC_A,    KC_S,    KC_D, LSFT_T(KC_F), KC_G,                    KC_H, RSFT_T(KC_J), KC_K,    KC_L,    KC_SCLN, TD(TD_QUOT),
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_NO,    KC_MUTE, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSHIFT,
                             KC_NO, KC_LALT, MO(_LOWER), LCTL_T(KC_SPC),  LT(_FN, KC_ENTER),  MO(_RAISE),   KC_NO, KC_CCCV
  ),

  [_LOWER] = LAYOUT(
  KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS,  KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TILD,     KC_NO,   KC_NO,   KC_UP,     KC_NO,    KC_NO,                     KC_NO,   KC_7,   KC_8, KC_9,  KC_KP_MINUS,  KC_TRNS,
  KC_TRNS,     KC_NO,   KC_LEFT, KC_DOWN,   KC_RIGHT, KC_NO,                     KC_NO,   KC_4,   KC_5, KC_6,  KC_KP_PLUS,   KC_NO,
  KC_CAPSLOCK, KC_NO,   KC_HOME, KC_PGDOWN, KC_END,   KC_NO,  KC_TRNS,   KC_NO,  KC_NO,   KC_1,   KC_2, KC_3,  KC_DOT,   KC_TRNS,
                             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_TRNS, KC_UNRE
  ),

  [_RAISE] = LAYOUT( 
  KC_ESC,  KC_NO,   KC_NO,  KC_NO,    KC_NO,       KC_NO,                                    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,
  KC_ESC,  KC_EXLM, KC_AT,  KC_HASH,  KC_DLR,      KC_PERC,                                  KC_AMPR, KC_ASTR, KC_LCBR, KC_RCBR, KC_BSLS,   KC_DELETE,
  KC_TRNS, KC_NO,   KC_NO,  KC_NO,    KC_NO,       KC_CIRC,                                    KC_MINS, KC_EQL,  KC_LPRN, KC_RPRN, KC_COLON,  KC_GRV,
  KC_TRNS, KC_NO,   KC_NO,  KC_LEFT_ANGLE_BRACKET, KC_RIGHT_ANGLE_BRACKET, KC_NO, KC_TRNS,   KC_NO,   KC_UNDS, KC_QUESTION, KC_LBRC, KC_RBRC, KC_PIPE,      KC_TRNS,
                            KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS, KC_SELCUT
  ),

  [_FN] = LAYOUT(
  XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F12,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_INSERT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______,  _______,  _______, _______, _______
  )
};


static uint16_t copy_paste_timer;
static uint16_t select_cut_timer;
static uint16_t undo_redo_timer; 

qk_tap_dance_action_t tap_dance_actions[] = {[TD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DOUBLE_QUOTE)};


int RGB_current_mode;

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
#endif
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
//const char *read_keylog(void);
//const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    oled_write_ln(read_layer_state(), false);
    //oled_write_ln(read_keylog(), false);
    //oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
     case KC_CCCV:  // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                    tap_code16(LCTL(KC_C));
                } else {
                    tap_code16(LCTL(KC_V));  // Tap, paste
                }
            }
            break;
        case KC_SELCUT:
            if (record->event.pressed) {
                select_cut_timer = timer_read();
            } else {
                if (timer_elapsed(select_cut_timer) > TAPPING_TERM) {  // Hold, cut
                    tap_code16(LCTL(KC_X));
                } else {
                    tap_code16(LCTL(KC_A));  // Tap, select all
                }
            }
            break;
        case KC_UNRE:
            if (record->event.pressed) {
                undo_redo_timer = timer_read();
            } else {
                if (timer_elapsed(undo_redo_timer) > TAPPING_TERM) {  // Hold, redo
                    tap_code16(LCTL(KC_Z));
                } else {
                    tap_code16(LCTL(KC_Z));  // Tap, undo
                }
            }
            break;
    // case QWERTY:
    //   if (record->event.pressed) {
    //     set_single_persistent_default_layer(_QWERTY);
    //   }
    //   return false;
    //   break;
    // case LOWER:
    //   if (record->event.pressed) {
    //     layer_on(_LOWER);
    //   } else {
    //     layer_off(_LOWER);
    //   }
    //   update_tri_layer(_LOWER, _RAISE, _FN);
    //   return false;
    //   break;
    // case RAISE:
    //   if (record->event.pressed) {
    //     layer_on(_RAISE);
    //   } else {
    //     layer_off(_RAISE);
    //   }
    //   update_tri_layer(_LOWER, _RAISE, _FN);
    //   return false;
    //   break;
    // case FN:
    //     if (record->event.pressed) {
    //       layer_on(_FN);
    //     } else {
    //       layer_off(_FN);
    //     }
    //     return false;
    //     break;
  }
  return true;
}

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

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
       oled_write_ln_P(PSTR("2222"), false);
      tap_code(KC_MS_WH_UP);
    } else {
       oled_write_ln_P(PSTR("3333"), false);
      tap_code(KC_MS_WH_DOWN);
    }
}
#endif
