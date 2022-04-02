/* A standard layout for the Dactyl Manuform 5x6 Keyboard */

#include QMK_KEYBOARD_H

//Tap Dance
#ifdef TAP_DANCE_ENABLE
// Tap Dance declarations
enum {
    TD_ESC_LGUI,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_LGUI] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_LGUI),
};

#endif

// Layers
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_5x6(
    TD(TD_ESC_LGUI),    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                KC_6,   KC_7,   KC_8   ,    KC_9  ,   KC_0,       KC_MINS,
    KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                        KC_Y,   KC_U,   KC_I   ,    KC_O  ,   KC_P,       KC_BSLS,
    KC_EQL,     KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                        KC_H,   KC_J,   KC_K   ,    KC_L  ,   KC_SCLN,    KC_QUOT,
    KC_LSFT,    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                        KC_N,   KC_M,   KC_COMM,    KC_DOT,   KC_SLSH,    KC_RSFT,
               KC_LEFT , KC_RGHT,                                                KC_LBRC, KC_RBRC,
                                        KC_BSPC, XXX,                                XXX, KC_SPC,
                                                    KC_DEL,  KC_LALT,       KC_RALT, KC_ENT,
                                                    KC_LCTL , LOWER,       RAISE,  KC_RCTL
  ),

  [_LOWER] = LAYOUT_5x6(

        XXX, XXX, XXX, XXX, XXX, XXX,            KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,   XXX,
        XXX, XXX, XXX, XXX, XXX, XXX,            XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX,            XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX,            XXX, XXX, XXX, XXX, XXX , XXX,
                XXX, XXX,                          KC_F11, KC_F12,
                            XXX, XXX,                        XXX, XXX,
                                XXX, XXX,            XXX, XXX,
                                XXX, XXX,            XXX,  XXX

  ),

  [_RAISE] = LAYOUT_5x6(
     KC_CAPS, KC_F1,  KC_F2, KC_F3, KC_F4, KC_F5,             KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,
     XXX, XXX, XXX, XXX, XXX,  XXX,             XXX, XXX, XXX, XXX, XXX, XXX,
     KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,               XXX, XXX, XXX, XXX, XXX, XXX,
     KC_GRV, KC_BSLS, XXX, XXX, XXX, XXX,             XXX,  XXX, XXX, XXX, XXX, XXX,

                        KC_UP, KC_DOWN,                                                  XXX, XXX,
                                           XXX, XXX,            XXX, XXX,
                                           XXX, XXX,            XXX,  KC_UP,
                                           KC_PGDN,  KC_PGUP,             XXX, XXX
  )
};


void keyboard_post_init_user(void) {
    #ifdef CONSOLE_ENABLE
        debug_enable=true;
        debug_matrix=true;
        debug_keyboard=true;
    #endif
}

uint8_t prev_rgblight_mode = RGBLIGHT_DEFAULT_MODE;
bool led_update_user(led_t led_state) {
    if(led_state.caps_lock){
        prev_rgblight_mode = rgblight_get_mode();
        rgblight_sethsv_noeeprom(0, RGBLIGHT_DEFAULT_SAT, 255);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING+2);
    }else{
        rgblight_mode_noeeprom(RGBLIGHT_DEFAULT_MODE);
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);

    if(is_keyboard_left()){
        dprintf("Is LEFT part\n");
    }else{
        dprintf("Is RIGHT part\n");
    }
#endif

    if(is_keyboard_left()){
        if(matrix_get_row(5) & (1 << 3)){
            if(matrix_get_row(4) & (1 << 4)){
                eeconfig_disable();
                bootloader_jump();
                return false;
            }
        }
    } else {
        if(matrix_get_row(10) & (1 << 1)){
            if(matrix_get_row(11) & (1 << 2)){
                eeconfig_disable();
                bootloader_jump();
                return false;
            }
        }
    }

    return true;
}

// Rotary encoder related code
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 1) { // Encoder on master side
    if(IS_LAYER_ON(_RAISE)) { // on Raise layer
      // Cursor control
      if (clockwise) {
          tap_code(KC_MNXT);
      } else {
          tap_code(KC_MPRV);
      }
    }
    else {
      if (clockwise) {
          tap_code(KC_VOLU);
      } else {
          tap_code(KC_VOLD);
      }
    }
  }
  else if (index == 0) { // Encoder on slave side
    if(IS_LAYER_ON(_LOWER)) { // on Lower layer
      //
      if (clockwise) {
          tap_code(KC_RIGHT);
      } else {
          tap_code(KC_LEFT);
      }
    }
    else {
      if (clockwise) {
          tap_code(KC_DOWN);
      } else {
          tap_code(KC_UP);
      }
    }
  }
    return true;
}
#endif
