/* Copyright 2021 Nathan Spears
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

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

enum custom_keycodes {
    WELLSKATE = SAFE_RANGE,
    SHATTERSKATE = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case WELLSKATE:
            if (record->event.pressed){
                SEND_STRING("3" SS_DELAY(500) SS_TAP(KC_BTN2) SS_DELAY(100) " " SS_DELAY(5) SS_TAP(KC_F));
            } else {
            }
            break;
        case SHATTERSKATE:
            if (record->event.pressed){
                SEND_STRING("3" SS_DELAY(500) SS_TAP(KC_BTN2) SS_DELAY(100) " " SS_DELAY(5) SS_TAP(KC_X));
            } else {
            }
            break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base Layer
     * .--------------------------------------------------------------------------------------------------------------------------------------------------'
     * |  ESC      | 1      | 2      | 3      | 4      | 5      |        | PSCR   |        |        |6       | 7      | 8      | 9      | 0      | DEL    |
     * |-----------+--------+--------+------- +--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | TAB       | Q      | W      | E      | R      | T      | INSERT | HOME   |        |        | Y      | U      | I      | O      | P      | BCKSPC |
     * |-----------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | CAPS      | A      | S      | D      | F      | G      | DEL    | SCRLCK |        |        | H      | J      | K      | L      | ;:     | '"     |
     * |-----------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+------- +--------+--------+--------+--------|
     * | LSHIFT    | Z      | X      | C      | V      | B      | PSCR   | PAUS   |        |        | N      | M      | ,      | .      | UP     | RSHIFT |
     * |-----------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
     * | LCTRL     | MENU   | LGUI   |  LALT  | SPACE  | SPACE  |SPACE   |Lyr1,SPC| SPACE  | SPACE  | RALT   | RGUI   | RCTRL  | LEFT   | DOWN   | RIGHT  |
     * '--------------------------------------------------------------------------------------------------------------------------------------------------'
     */
    [0] = LAYOUT_grid(
      KC_ESC,   KC_1,    KC_2,    KC_3,     KC_4,    KC_5,    _______,   KC_PSCR,    _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
      KC_TAB,   KC_Q,    KC_W,    KC_E,     KC_R,    KC_T,    KC_LBRC,   KC_F1,      KC_HOME, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
      MO(1),     KC_A,    KC_S,    KC_D,     KC_F,    KC_G,    KC_EQL,    KC_F2,      KC_END,  KC_MINUS, KC_H,   KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
      KC_LSFT,  KC_Z,    KC_X,    KC_C,     KC_V,    KC_B,    KC_BSLS,   KC_F3,      KC_GRV,  KC_SLSH, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,  KC_RSFT,
      KC_LCTL,  KC_MENU, KC_LGUI, KC_LALT,  KC_SPC,  KC_SPC,  KC_SPC, LT(1, KC_SPC), KC_SPC,  KC_SPC,  KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT
    ),

    /* Function Layer
     * .----------------------------------------------------------------------------------------------------------------------------------------------'
     * | `      | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | F12    | F13   | DEL    |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------+--------+--------|
     * |        |        | MENU   |        |        |        |        |        |        |        |        |        | PRT SC |       |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+-------+--------+--------|
     * |        |        |        |        |        |        |        |        |        |        |        |        |        | RESET |        |        |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+-------+--------+--------|
     * |        |        |        |        |        |        |        |        |        | MUTE   | VOL DN | VOL UP | \      |       |        |        |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+--------+--------+-------+--------+--------|
     * | RESET  | RESET  | TT(2)  |        |        |        |        |        |        |        |        |        |        |       |        |        |
     * '----------------------------------------------------------------------------------------------------------------------------------------------'
     */
    [1] = LAYOUT_grid(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_F13, KC_DEL, _______,
        _______, _______, KC_APP,  _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, _______, _______, _______,
        _______, _______, _______, KC_F13, WELLSKATE, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_BSLS, _______, _______, _______,
        _______, _______,   TT(2), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    /* 2nd Function Layer
     * .---------------------------------------------------------------------------------------------------------------------------------------------'
     * |        |        |RGB ON OFF|HUE INC|HUE DEC|SAT INC |SAT DEC |        |        |        |        |        |        |       |PRNSCRN |       |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------+--------+-------|
     * | `      | 1      | 2      | 3      | 4      | 5      |        |        |        | 6      | 7      | 8      | 9      |  0    |        |       |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+-------+--------+-------|
     * |  ~     | !      |  @     |  #     |  $     |  %     |        |        |        |  ^     |  &     |  *     |  (     |  )    | BCKSPC |       |
     * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+-------+--------+-------|
     * |        |        |        |        |        |        |        |        |        | MUTE   | VOL DN | VOL UP | \      |       |        |       |
     * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+-------+--------+-------|
     * | RESET  | RESET  |        |        |        |        |        |        |        |        |        |        |        |       |        |       |
     * '---------------------------------------------------------------------------------------------------------------------------------------------'
     */
    [2] = LAYOUT_grid(
        _______, _______, RGB_TOG, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, _______, _______, _______, _______, _______, _______, _______, KC_PSCR, _______,
        KC_GRV,     KC_1,   KC_2,     KC_3,    KC_4,    KC_5, _______, _______, _______,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______, _______,
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_BSLS, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
};
