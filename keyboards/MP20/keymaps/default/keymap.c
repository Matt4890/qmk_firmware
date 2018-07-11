/* Copyright 2018 Matthew Allwright
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Layers
enum MP20_layers {
  _NUMPAD = 0,
  _WRKSPC,
  _ARROWS,
  _MACROS,
  _MOD
};

// Custom Keycodes
enum MP20_keycodes {
  TD_WRKSPC,
  TD_ARROWS,
  BOOP
};

// Tap Dance Keys
#define TD_WKSP TD(TD_WRKSPC)
#define TD_ARWS TD(TD_ARROWS)

// Windows workspace controls
#define WwsN LCTL(LGUI(KC_D))
#define WwsQ LCTL(LGUI(KC_F4))
#define WwsL LCTL(LGUI(KC_LEFT))
#define WwsR LCTL(LGUI(KC_RGHT))

// Linux workspace controls
// #define LwsU LCTL(LALT(KC_UP))
// #define LwsD LCTL(LALT(KC_DOWN))
// #define LwsL LCTL(LALT(KC_LEFT))
// #define LwsR LCTL(LALT(KC_RGHT))

// Commands
#define COPY    LCTL(KC_C)
#define CUT     LCTL(KC_X)
#define PASTE   LCTL(KC_V)
#define SAVE    LCTL(KC_S)
#define SLCTALL LCTL(KC_A)
#define UNDO    LCTL(KC_Z)

// Pretty Things
#define _______ KC_TRNS
#define ___X___ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Numpad
 * ,----------------------------------.
 * |   7  |   8  |   9  |Worksp|Arrows|
 * |------+------+------+------+------|
 * |   4  |   5  |   6  |MPrev |MNext |
 * |------+------+------+------+------|
 * |   1  |   2  |   3  | Mute |MPl/Pa|
 * |------+------+------+------+------|
 * |   0  |   .  |Enter | Vol- | Vol+ |
 * `----------------------------------'
 */
[_NUMPAD] = {
  {KC_KP_7, KC_KP_8, KC_KP_9, TD_WKSP, TD_ARWS },
  {KC_KP_4, KC_KP_5, KC_KP_6, KC_MPRV, KC_MNXT },
  {KC_KP_1, KC_KP_2, KC_KP_3, KC_MUTE, KC_MPLY },
  {KC_KP_0, KC_PDOT, KC_PENT, KC_VOLD, KC_VOLU }
},

/* Workspace
 * ,----------------------------------.
 * | Alt  | WwsN |  F4  |      |      |
 * |------+------+------+------+------|
 * | WwsL | WwsQ | WwsR |      |      |
 * |------+------+------+------+------|
 * |SelAll| Save | Undo |      |      |
 * |------+------+------+------+------|
 * | Cut  | Copy |Paste |      |      |
 * `----------------------------------'
 */
[_WRKSPC] = {
  {KC_LALT, WwsN,    KC_F4,   _______, _______ },
  {WwsL,    WwsQ,    WwsR,    _______, _______ },
  {SLCTALL, SAVE,    UNDO,    _______, _______ },
  {CUT,     COPY,    PASTE,   _______, _______ }
},

/* Arrows
 * ,----------------------------------.
 * | Ins  | Home | PgUp |      |      |
 * |------+------+------+------+------|
 * | Del  | End  | PgDn |      |      |
 * |------+------+------+------+------|
 * |      |  Up  |      |      |      |
 * |------+------+------+------+------|
 * | Left | Down |Right |      |      |
 * `----------------------------------'
 */
[_ARROWS] = {
  {KC_INS,  KC_HOME, KC_PGUP, _______, _______ },
  {KC_DEL,  KC_END,  KC_PGDN, _______, _______ },
  {___X___, KC_UP,   ___X___, _______, _______ },
  {KC_LEFT, KC_DOWN, KC_RGHT, _______, _______ }
},

/* Macros
 * ,----------------------------------.
 * |      |      |NumLck|      |      |
 * |------+------+------+------+------|
 * | Boop | Boop | Boop |      |      |
 * |------+------+------+------+------|
 * | Boop | Boop | Boop |      |      |
 * |------+------+------+------+------|
 * |      |      |      |      |      |
 * `----------------------------------'
 */
[_MACROS] = {
  {___X___, ___X___, KC_NLCK, _______, _______ },
  {BOOP,    BOOP,    BOOP,    _______, _______ },
  {BOOP,    BOOP,    BOOP,    _______, _______ },
  {___X___, ___X___, ___X___, _______, _______ }
}

};

void dance_wrkspc_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_invert(_WRKSPC);
    layer_off(_ARROWS);
    layer_off(_MACROS);
  } else if (state->count == 2)  {
    layer_off(_WRKSPC);
    layer_off(_ARROWS);
    layer_invert(_MACROS);
  }
}

void dance_arrows_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_off(_WRKSPC);
    layer_invert(_ARROWS);
    layer_off(_MACROS);
  } else if (state->count == 2)  {
    layer_off(_WRKSPC);
    layer_off(_ARROWS);
    layer_invert(_MACROS);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {

  [TD_WRKSPC]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_wrkspc_finished, NULL),
  [TD_ARROWS]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_arrows_finished, NULL)

};

// uint32_t layer_state_set_user(uint32_t s) {
//   return update_tri_layer_state(s, _WRKSPC, _ARROWS, _MACROS);
// }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (record->event.pressed) {

    switch(keycode) {

      case BOOP:
        SEND_STRING("Boop. ");
        return false;
        break;

    }

  }

  return true;

}