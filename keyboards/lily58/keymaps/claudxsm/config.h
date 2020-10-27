/*
Attribution-ShareAlike 4.0 International (CC BY-SA 4.0) 2020 Max Drasbeck 
 *
 * You are free to:
 *
 *  Share — copy and redistribute the material in any medium or format
 *  Adapt — remix, transform, and build upon the material
 *   for any purpose, even commercially.
 *
 * The licensor cannot revoke these freedoms as long as you follow the license terms.
*/

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define USE_SERIAL_PD2

#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }
#define ENCODER_RESOLUTION 4

// #define TAPPING_FORCE_HOLD
// #define TAPPING_TERM 180

#define TAPPING_TERM 300
#define TAPPING_TERM_PER_KEY
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD


// #undef RGBLED_NUM
// #define RGBLIGHT_ANIMATIONS
// #define RGBLED_NUM 27
// #define RGBLIGHT_LIMIT_VAL 120
// #define RGBLIGHT_HUE_STEP 10
// #define RGBLIGHT_SAT_STEP 17
// #define RGBLIGHT_VAL_STEP 17

// Underglow
/*
#undef RGBLED_NUM
#define RGBLED_NUM 14    // Number of LEDs
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP
*/


// don't think any of these are working yet

//#define MOUSEKEY_WHEEL_DELAY 300        //Delay between pressing a wheel key and wheel movement
// #define MOUSEKEY_WHEEL_INTERVAL 5     //Time between wheel movements, low=fast
// #define MOUSEKEY_WHEEL_MAX_SPEED 200      //Maximum number of scroll steps per scroll action
// #define MOUSEKEY_WHEEL_TIME_TO_MAX 40   //Time until maximum scroll speed is reached
#define MK_3_SPEED 
#define MK_W_OFFSET_0 1     //Scroll steps per scroll action (KC_ACL2)
#define MK_W_INTERVAL_0 5  //Time between scroll steps (KC_ACL2)

