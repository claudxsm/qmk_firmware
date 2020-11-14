
#include QMK_KEYBOARD_H
#include <stdio.h>
#include "lily58.h"

// #define L_BASE 0
// #define L_LOWER (1 << 1)
// #define L_RAISE (1 << 2)
// #define L_ADJUST (1 << 3)
// #define L_ADJUST_TRI (L_ADJUST | L_RAISE | L_LOWER)


enum layers {
  _BASE,
  _GAMING,
  _LOWER,
  _RAISE,
  _FN
};


char layer_state_str[24];

const char *read_layer_state(void) {
  switch (get_highest_layer(layer_state))
  {
  case _BASE:
    snprintf(layer_state_str, sizeof(layer_state_str), " ");
    break;
  case _RAISE:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Raise");
    break;
  case _LOWER:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Lower");
    break;
  case _FN:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: FN");
    break;
  case _GAMING:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Gaming");
    break;
  default:
    snprintf(layer_state_str, sizeof(layer_state_str), "Layer: ???");
   // snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state);
  }

  return layer_state_str;
}
