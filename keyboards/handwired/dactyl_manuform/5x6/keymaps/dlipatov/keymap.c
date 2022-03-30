/* A standard layout for the Dactyl Manuform 5x6 Keyboard */

#include QMK_KEYBOARD_H

//Tap Dance
#ifdef TAP_DANCE_ENABLE
// Tap Dance declarations
enum {
    TD_ESC_CAPS,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
};

#endif

// Combo
#ifdef COMBO_ENABLE
const uint16_t PROGMEM test_combo1[] = {KC_A, KC_B, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
     COMBO(test_combo1, KC_ESC)
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
    KC_ESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,                         KC_6,   KC_7,   KC_8   ,    KC_9  ,   KC_0,       KC_MINS,
    KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,                        KC_Y,   KC_U,   KC_I   ,    KC_O  ,   KC_P,       KC_BSLS,
    KC_EQL,     KC_A,   KC_S,   KC_D,   KC_F,   KC_G,                        KC_H,   KC_J,   KC_K   ,    KC_L  ,   KC_SCLN,    KC_QUOT,
    KC_LSFT,    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                        KC_N,   KC_M,   KC_COMM,    KC_DOT,   KC_SLSH,    KC_RSFT,
               KC_LEFT , KC_RGHT,                                                KC_LBRC, KC_RBRC,
                                        KC_BSPC, _______,                                _______, KC_SPC,
                                                    KC_DEL,  KC_LGUI,       KC_DOWN, KC_ENT,
                                                    KC_LCTL , LOWER,       RAISE,  KC_RCTL
  ),

  [_LOWER] = LAYOUT_5x6(

     _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,              KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
     _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
     _______, KC_CAPS, KC_INS,  KC_HOME, KC_END,   KC_PSCR,             _______, _______, _______, _______, _______, _______,
     _______, KC_UNDO, KC_CUT,  KC_COPY, KC_PASTE, _______,             _______, _______, _______, _______, _______ , _______,
                       _______, _______,                                                 KC_LCBR, KC_RCBR,
                                            _______, _______,           _______, _______,
                                            _______, _______,            _______, _______,
                                            _______, _______,            _______,  _______

  ),

  [_RAISE] = LAYOUT_5x6(
     KC_CAPS, _______, _______, _______, _______,  _______,             _______, _______, _______, _______, _______, _______,
     _______, _______, _______, _______, _______,  _______,             _______, _______, _______, _______, _______, _______,
     KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,               KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,
     _______,  _______, _______, _______, _______, _______,             _______,  _______, _______, _______, _______, _______,

                        KC_GRV, KC_BSLS,                                                  _______, _______,
                                           _______, _______,            _______, _______,
                                           _______, _______,            _______,  KC_UP,
                                           KC_PGDN,  KC_PGUP,             _______, _______
  )
};

//Lighting Layers

// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 24, HSV_RED}     // Light 4 LEDs, starting with LED 12
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 24, HSV_GOLD}
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 24, HSV_AZURE}
);


// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_layer1_layer,    // Overrides caps lock layer
    my_layer2_layer    // Overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    return state;
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
