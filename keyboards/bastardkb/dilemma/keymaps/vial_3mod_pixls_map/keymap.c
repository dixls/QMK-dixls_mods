/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_NUM,
    LAYER_SYM,
    LAYER_NAV,
    LAYER_NAV_TWO,
    LAYER_POINTER,
};

// Automatically enable sniping-mode on the pointer layer.
#define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum combos {
    ESCW_Q,
    OP_BSP,
    ON_BSP,
    ED_CAPS,
};

const uint16_t PROGMEM qw_combo[] = {KC_ESC, KC_W, COMBO_END};
const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM on_combo[] = {KC_9, KC_0, COMBO_END};
const uint16_t PROGMEM ed_combo[] = {KC_ESC, KC_DEL, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [ESCW_Q] = COMBO(qw_combo, KC_Q),
    [OP_BSP] = COMBO(op_combo, KC_BSPC),
    [ON_BSP] = COMBO(on_combo, KC_BSPC),
    [ED_CAPS] = COMBO(ed_combo, CAPS_WORD),
};

#define SPC_NUM LT(LAYER_NUM, KC_SPC)
#define TAB_NAV LT(LAYER_NAV, KC_TAB)
#define ENT_SYM LT(LAYER_SYM, KC_ENT)
#define BSP_NAV LT(LAYER_NAV_TWO, KC_BSPC)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)

#define WRD_L LCTL(KC_LEFT)
#define WRD_R LCTL(KC_RIGHT)
#define WRD_U LCTL(KC_UP)
#define WRD_D LCTL(KC_DOWN)

#define SEL_L LSFT(KC_LEFT)
#define SEL_R LSFT(KC_RIGHT)
#define SEL_U LSFT(KC_UP)
#define SEL_D LSFT(KC_DOWN)
#define SEL_H LSFT(KC_HOME)
#define SEL_E LSFT(KC_END)

#define SWRD_L RCS(KC_LEFT)
#define SWRD_R RCS(KC_RIGHT)
#define SWRD_U RCS(KC_UP)
#define SWRD_D RCS(KC_DOWN)

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                                    \
     KC_ESC,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, \
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L, KC_QUOT, \
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                      KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, \
                                KC_ESC, SPC_NUM, TAB_NAV, BSP_NAV, ENT_SYM,  KC_DEL


/** \brief NUM and SYMBOL layer */
#define LAYOUT_LAYER_NUM        \
       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, \
           ,        ,        ,        ,        ,                          , KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, \
    KC_TILD,        ,        ,        ,        ,                          , KC_PIPE,        ,        , KC_SCLN, \
                               XXXXXXX, _______, XXXXXXX, KC_BSPC,  KC_ENT,  KC_DEL


/** \brief NAV layer and more symbols */
#define LAYOUT_LAYER_SYM        \
    S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),                   S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), \
           , KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                          , KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, \
     KC_GRV,        ,        ,        ,        ,                          , KC_PIPE,        ,        , KC_COLN, \
                                KC_ESC,  KC_SPC,  KC_TAB, KC_BSPC, _______,  KC_DEL


/** \brief NAV layer and more symbols */
#define LAYOUT_LAYER_NAV        \
           ,        ,   KC_UP,        , KC_PGUP,                          ,        ,   KC_UP,        ,        , \
           , KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                   KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, \
           ,        ,        ,        ,        ,                          ,        ,        ,        ,        , \
                               XXXXXXX, XXXXXXX, _______, KC_BSPC,  KC_ENT,  KC_DEL

/** \brief NAV layer and more symbols */
#define LAYOUT_LAYER_NAV_TWO        \
           ,        ,   WRD_U,        ,        ,                          ,        ,   SEL_U,        ,        , \
           ,   WRD_L,   WRD_D,   WRD_R,        ,                     SEL_H,   SEL_L,   SEL_D,   SEL_R,   SEL_E, \
           ,        ,        ,        ,        ,                          ,        ,        ,        ,        , \
                                KC_ESC, KC_LGUI, XXXXXXX, _______, XXXXXXX, XXXXXXX

/** \brief Mouse emulation and pointer functions. */
#define LAYOUT_LAYER_POINTER                                                                                    \
    XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,                   S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, \
    ______________HOME_ROW_GACS_L______________,                   ______________HOME_ROW_GACS_R______________, \
    _______, DRGSCRL, SNIPING, EEP_RST, QK_BOOT,                   QK_BOOT, EEP_RST, SNIPING, DRGSCRL, _______, \
                               KC_BTN3, KC_BTN1, KC_BTN2, KC_BTN2, KC_BTN1, KC_BTN3

/**
 * \brief Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     HOME_ROW_MOD_SCGA(LAYER_ALPHAS_QWERTY)
 */
#define _HOME_ROW_MOD_SCGA(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LCTL_T(L10), LGUI_T(L11), LALT_T(L12),        L13,         L14,  \
             R15,         R16,  RALT_T(R17), LGUI_T(R18), RCTL_T(R19), \
      LSFT_T(L20),        L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,  RSFT_T(R29), \
      __VA_ARGS__
#define HOME_ROW_MOD_SCGA(...) _HOME_ROW_MOD_SCGA(__VA_ARGS__)

/**
 * \brief Add pointer layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYER_ALPHAS_QWERTY` defined above, eg.:
 *
 *     POINTER_MOD(LAYER_ALPHAS_QWERTY)
 */
#define _POINTER_MOD(                                                  \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
             L10,         L11,         L12,         L13,         L14,  \
             R15,         R16,         R17,         R18,         R19,  \
      _L_PTR(L20),        L21,         L22,         L23,         L24,  \
             R25,         R26,         R27,         R28,  _L_PTR(R29), \
      __VA_ARGS__
#define POINTER_MOD(...) _POINTER_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    POINTER_MOD(HOME_ROW_MOD_SCGA(LAYOUT_LAYER_BASE))
  ),
  [LAYER_NUM] = LAYOUT_wrapper(LAYOUT_LAYER_NUM),
  [LAYER_SYM] = LAYOUT_wrapper(LAYOUT_LAYER_SYM),
  [LAYER_NAV] = LAYOUT_wrapper(LAYOUT_LAYER_NAV),
  [LAYER_NAV_TWO] = LAYOUT_wrapper(LAYOUT_LAYER_NAV_TWO),
  [LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > DILEMMA_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= DILEMMA_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
    }
}
#    endif // DILEMMA_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE
