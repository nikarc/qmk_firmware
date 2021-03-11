#include QMK_KEYBOARD_H

bool arrow_or_letter_key(uint16_t direction, uint16_t key, uint8_t mod_state, keyrecord_t *record);

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _QW 0
#define _DV 1
#define _CM 2
#define _L1 3
#define _L2 4
#define _L3 5
#define RGBLIGHT_EFFECT_BREATHING 2

// Curly braces have their own keys. These are defined to make them not mess up
// the grid in layer 2.
#define L_CURBR LSFT(KC_LBRC)
#define R_CURBR LSFT(KC_RBRC)
#define CTLESC MT(MOD_LCTL, KC_ESC)

enum custom_keycodes {
  DVORAK = SAFE_RANGE,
  QWERTY,
  COLEMAK
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QW] = LAYOUT( /* Qwerty */
            KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
            CTLESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            MO(_L1), KC_LALT, KC_LGUI,                   KC_ENT,  KC_SPC,                    KC_RGUI, KC_RALT,  TG(_L2)
            ),
    [_DV] = LAYOUT( /* Dvorak */
            KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC,
            CTLESC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,
            KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT,
            MO(_L1), KC_LALT, KC_LGUI,                   KC_ENT,  KC_SPC,                    KC_RGUI, KC_RALT,  TG(_L2)
            ),
    [_CM] = LAYOUT( /* Colemak */
            KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
            MO(_L1), KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    MO(_L1),
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, MO(_L2),
            KC_LCTL, MO(_L2), KC_LGUI,                   KC_ENT,  KC_SPC,                    KC_RALT, KC_ESC,  TG(_L3)
            ),
    [_L1] = LAYOUT( /* LAYER 1 */
            KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_7,    KC_8,    KC_9,    KC_LBRC,  _______,
            KC_ESC, KC_BSLS, KC_PIPE, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_4,    KC_5,    KC_6,    KC_RBRC,  KC_MINS,
            _______, _______,  _______, KC_PSCR, _______, _______, KC_0,   KC_1,    KC_2,    KC_3,    KC_EQL,   KC_SLSH,
            _______, _______, _______,                   _______, _______,                   _______, _______,  RESET
            ),
    [_L2] = LAYOUT( /* LAYER 2 */
            _______, QWERTY,  DVORAK,  _______, _______, _______, _______,   KC_F7,    KC_F8,    KC_F9,    KC_F10,    _______,
            KC_ESC,  KC_PIPE, KC_DQUO, KC_UNDS, KC_PLUS, L_CURBR,   R_CURBR, KC_F4,    KC_F5,    KC_F6,    _______,   _______,
            _______, _______, _______, _______, _______,  _______,   KC_F11,  KC_F1,    KC_F2,    KC_F3,    _______,   _______,
            _______, _______, _______,                   _______, _______,                       _______,  _______,   _______
            ),
     /* LAYER 3
    [_L3] = LAYOUT(
            _______, _______, _______, _______, _______, _______, _______, KC_P7, KC_P8, KC_P9, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, KC_P4, KC_P5, KC_P6, _______, _______,
            _______, _______, _______, _______, _______, _______, KC_P0, KC_P1, KC_P2, KC_P3, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______
            )
    */
};

void keyboard_post_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    // set up rgb effects on only the first led (index 0)
    rgblight_set_effect_range(0, 1);

    // set led effects to breathing mode in warm white
    // rgblight_sethsv_noeeprom(38, 191, 198);
    // rgblight_mode_noeeprom(RGBLIGHT_EFFECT_BREATHING + 2);
    sethsv(38, 191, 198, (LED_TYPE *)&led[0]);
    //rgblight_mode_noeeprom(RGBLIGHT_EFFECT_BREATHING + 2);

    // set other led's to off
    setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
    setrgb(0, 0, 0, (LED_TYPE *)&led[2]);
    rgblight_set();
  #endif
}

layer_state_t layer_state_set_user(layer_state_t state) {
  // state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  #ifdef RGBLIGHT_ENABLE
    /*if (layer_state_cmp(state, _ADJUST)) {
      setrgb(70, 255, 200, (LED_TYPE *)&led[0]);
      setrgb(255, 70, 100, (LED_TYPE *)&led[1]);
    } else if (layer_state_cmp(state, _LOWER)) {
      setrgb(70, 255, 200, (LED_TYPE *)&led[0]);
      setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
    } else if (layer_state_cmp(state, _RAISE)) {
      setrgb(0, 0, 0, (LED_TYPE *)&led[0]);
      setrgb(255, 70, 100, (LED_TYPE *)&led[1]);
    } else if (layer_state_cmp(state, _UTIL)) {
      setrgb(200, 70, 225, (LED_TYPE *)&led[0]);
      setrgb(200, 70, 225, (LED_TYPE *)&led[1]);
    } else if (layer_state_cmp(state, _MOUSE)) {
      setrgb(255, 145, 5, (LED_TYPE *)&led[0]);
      setrgb(255, 145, 5, (LED_TYPE *)&led[1]);
    } else {
      setrgb(0, 0, 0, (LED_TYPE *)&led[0]);
      setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
    }*/
  if (layer_state_cmp(state, _L1)) {
      setrgb(3, 236, 252, (LED_TYPE *)&led[1]);
  } else if (layer_state_cmp(state, _L2)) {
      setrgb(211, 3, 252, (LED_TYPE *)&led[2]);
  } else {
    setrgb(0, 0, 0, (LED_TYPE *)&led[1]);
    setrgb(0, 0, 0, (LED_TYPE *)&led[2]);
  }

  rgblight_set();
  #endif

  return state;
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

static uint8_t mod_state;
bool arrow_or_letter_key(uint16_t direction, uint16_t key, uint8_t mod_state, keyrecord_t *record) {
    static bool ctrl_registered;

    if (record->event.pressed) {
        if (mod_state & MOD_MASK_CTRL) {
            del_mods(MOD_MASK_CTRL);
            register_code(direction);
            ctrl_registered = true;
            set_mods(mod_state);
            return false;
        }
    } else {
        if (ctrl_registered) {
            unregister_code(direction);
            ctrl_registered = false;
            return false;
        } else {
            return true;
        }
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();
    switch(keycode) {
        case DVORAK:
            if (record->event.pressed) {
                persistent_default_layer_set(1UL<<_DV);
            }
            return false;
        case QWERTY:
            if (record->event.pressed) {
                persistent_default_layer_set(1UL<<_QW);
            }
            return false;
        case COLEMAK:
            if (record->event.pressed) {
                persistent_default_layer_set(1UL<<_CM);
            }
            return false;
        case KC_H: {
                return arrow_or_letter_key(KC_LEFT, KC_H, mod_state, record);
            }
        case KC_J: {
                return arrow_or_letter_key(KC_DOWN, KC_J, mod_state, record);
            }
        case KC_K: {
                return arrow_or_letter_key(KC_UP, KC_K, mod_state, record);
            }
        case KC_L: {
                return arrow_or_letter_key(KC_RIGHT, KC_L, mod_state, record);
            }
        default:
            return true;
    }
    return true;
};
