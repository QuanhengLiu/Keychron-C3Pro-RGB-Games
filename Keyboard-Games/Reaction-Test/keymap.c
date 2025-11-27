/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
#include "rgb_matrix.h" 
#include "stdlib.h"    
#include "timer.h"      

// ------------------------------------
//  Reaction Time Game Logic
// ------------------------------------

// 1. Custom Keycodes
enum custom_keycodes {
    START_GAME = SAFE_RANGE, 
};

// 2. Game States
enum game_states {
    STATE_IDLE,         
    STATE_TARGET_LIT, 
    STATE_WAITING,  
    STATE_GAME_WIN,
    STATE_FOUL          // False start / Penalty state
};

// 3. Global Variables
static uint8_t g_game_state = STATE_IDLE; 
static uint8_t g_target_led_index;   // Current target LED index
static uint16_t g_target_keycode;    // Current target keycode
static uint32_t g_target_start_time; // Timestamp when target lit up
static uint32_t g_reaction_time;     // Reaction time in milliseconds
static uint32_t g_wait_start_time;   // Timestamp when waiting started
static uint16_t g_wait_delay_ms;     // Random delay duration for current round

// 4. Target Database
// Mapping physical LED indices to Keycodes for the game
const uint8_t target_leds[] = {
    51, // A
    52, // S
    53, // D
    54, // F
    57, // J
    58, // K
    59, // L
    41  // I
};
const uint16_t target_keys[] = {
    KC_A, KC_S, KC_D, KC_F,
    KC_J, KC_K, KC_L, KC_I
};

const uint8_t num_targets = 8;

enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN,
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_tkl_ansi(
        KC_ESC,             KC_BRID,  KC_BRIU,  _______,  _______,  RM_VALD,  RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,   KC_VOLD,   KC_VOLU,  KC_NO,    KC_TRNS,  RM_NEXT,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,    KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,   KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LOPT,  KC_LCMD,                                START_GAME,                                 KC_RCMD, MO(MAC_FN), KC_APP,    KC_RCTL,KC_LEFT,  KC_DOWN,  KC_RGHT ),

    [MAC_FN] = LAYOUT_tkl_ansi(
        _______,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,     KC_F12,   _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        KC_OSSW,  RM_PREV, RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______ ),

    [WIN_BASE] = LAYOUT_tkl_ansi(
        KC_ESC,             KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12,   KC_PSCR,KC_SCROLL_LOCK,KC_PAUSE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,    KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,   KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,              KC_ENT,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(WIN_FN),KC_APP,    KC_RCTL,KC_LEFT,  KC_DOWN,  KC_RGHT ),

    [WIN_FN] = LAYOUT_tkl_ansi(
        _______,            KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RM_VALD,  RM_VALU,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,    KC_VOLU,  _______,  _______,  RM_NEXT,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        RM_TOGG,  RM_NEXT,  RM_VALU,  RM_HUEU,  RM_SATU,  RM_SPDU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,
        KC_OSSW,  RM_PREV, RM_VALD,  RM_HUED,  RM_SATD,  RM_SPDD,  _______,  _______,  _______,  _______,  _______,  _______,              _______,
        _______,            _______,  _______,  _______,  _______,  _______,  NK_TOGG,  _______,  _______,  _______,  _______,              _______,            _______,
        _______,  GU_TOGG,  _______,                                _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______ ),
};

// Start waiting phase
void start_new_round(void) {
    // 1. Calculate a random delay between 1000ms and 3000ms
    g_wait_delay_ms = (rand() % 2000) + 1000; 

    // 2. Record start timestamp
    g_wait_start_time = timer_read32();

    // 3. Set state to WAITING
    g_game_state = STATE_WAITING;
}

// Called when delay is over
void activate_target(void) {
    // 1. Select a random target
    uint8_t random_index = rand() % num_targets;
    g_target_led_index = target_leds[random_index];
    g_target_keycode = target_keys[random_index];
    
    // 2. Reset reaction time
    g_reaction_time = 0; 

    // 3. Set state to TARGET_LIT
    g_game_state = STATE_TARGET_LIT;

    // 4. Start timer for reaction measurement
    g_target_start_time = timer_read32(); 
}

// ------------------------------------------------
// Standard QMK Functions
// ------------------------------------------------

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(0, 0, 150); 
    
    // Initialize Random Number Generator with current timer seed
    srand(timer_read());

    g_game_state = STATE_IDLE; 
}

// Main Rendering Loop
bool rgb_matrix_indicators_kb(void) {
    
    // Check if wait time is over
    if (g_game_state == STATE_WAITING) {
        if (timer_elapsed32(g_wait_start_time) > g_wait_delay_ms) {
            activate_target();
        }
    }
    
    rgb_matrix_set_color_all(0, 0, 0);

    // --- State Machine Rendering ---

    if (g_game_state == STATE_IDLE) {
        // IDLE: ESC Red
        rgb_matrix_set_color(0, 255, 0, 0); 
    
    } else if (g_game_state == STATE_WAITING) {
        // WAITING: ESC Yellow
        rgb_matrix_set_color(0, 255, 255, 0); 

    } else if (g_game_state == STATE_TARGET_LIT) {
        // TARGET: Light up target Key Green
        rgb_matrix_set_color(g_target_led_index, 0, 255, 0); 
    
    } else if (g_game_state == STATE_FOUL) {
        // FOUL: False Start -> Flash ESC Red
        // Flash every 500ms
        if ((timer_read32() % 500) < 250) {
            rgb_matrix_set_color(0, 255, 0, 0); 
        }
        
    } else if (g_game_state == STATE_GAME_WIN) {
        // WIN: Scoreboard Display
        
        uint8_t r = 0, g = 0, b = 0; 
        uint8_t num_lights = 0;     

        // Determine score based on reaction time
        if (g_reaction_time < 200) {
            // < 200ms: Godlike (Cyan, 12 LEDs)
            r = 100; g = 255; b = 50;
            num_lights = 12; // F1 - F12
        } else if (g_reaction_time < 300) {
            // 200-300ms: Fast (Yellow, 8 LEDs)
            r = 255; g = 255; b = 0;
            num_lights = 8; // F1 - F8
        } else if (g_reaction_time < 500) {
            // 300-500ms: Average (Orange, 5 LEDs)
            r = 255; g = 100; b = 0;
            num_lights = 5; // F1 - F5
        } else {
            // > 500ms: Slow (Red, 3 LEDs)
            r = 255; g = 0; b = 0;
            num_lights = 3; // F1 - F3
        }

        // Highlight the target key
        rgb_matrix_set_color(g_target_led_index, r, g, b);

        // Light up the Scoreboard (F-Row)
        for (uint8_t i = 1; i <= num_lights; i++) {
            rgb_matrix_set_color(i, r, g, b);
        }
    }

    return true; 
}

// Key Processing
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    
    if (!record->event.pressed) {
        return true; 
    }

    // Check for Start Button
    if (keycode == START_GAME) {
        // Allow restart from Idle, Win, or Foul states
        if (g_game_state == STATE_IDLE || g_game_state == STATE_GAME_WIN || g_game_state == STATE_FOUL) { 
            start_new_round();
        }
        return false; 
    }

    // Check for False Start during Waiting phase
    if (g_game_state == STATE_WAITING) {
        // Check if pressed key is one of the targets
        for (uint8_t i = 0; i < num_targets; i++) {
            if (keycode == target_keys[i]) {
                // False Start detected!
                g_game_state = STATE_FOUL;
                return false; // Consume keypress
            }
        }
    }

    // Check for Win condition
    if (g_game_state == STATE_TARGET_LIT && keycode == g_target_keycode) {
        g_reaction_time = timer_elapsed32(g_target_start_time);
        g_game_state = STATE_GAME_WIN; 
    }

    return true; 
}