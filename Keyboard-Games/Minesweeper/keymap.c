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

// clang-format off

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
        KC_LCTL,  KC_LOPT,  KC_LCMD,                                KC_SPC,                                 KC_RCMD, MO(MAC_FN), KC_APP,    KC_RCTL,KC_LEFT,  KC_DOWN,  KC_RGHT ),

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

#include <stdlib.h>
#include "timer.h"

// 1. Game Configuration
#define MINE_ROWS 4
#define MINE_COLS 6
#define NUM_MINES 5  

// 2. Hardware Mapping
const uint8_t led_map[MINE_ROWS][MINE_COLS] = {
    { 17, 18, 19, 20, 21, 22 }, 
    { 34, 35, 36, 37, 38, 39 }, 
    { 51, 52, 53, 54, 55, 56 }, 
    { 64, 65, 66, 67, 68, 69 }  
};

const uint16_t key_map[MINE_ROWS][MINE_COLS] = {
    { KC_1, KC_2, KC_3, KC_4, KC_5, KC_6 },
    { KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y },
    { KC_A, KC_S, KC_D, KC_F, KC_G, KC_H },
    { KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N }
};

// 3. Data Structures
typedef struct {
    bool is_mine;
    bool is_visible;
    bool is_flagged;
    uint8_t neighbor_count; 
} Cell;

Cell game_board[MINE_ROWS][MINE_COLS];

// Game States
enum { 
    STATUS_BOOT,    // Boot animation sequence
    STATUS_IDLE,    // Animation done, waiting for start
    STATUS_PLAYING, // Game in progress
    STATUS_WON, 
    STATUS_LOST 
};

uint8_t game_status = STATUS_BOOT; // Start with boot animation
bool first_move = true;

// Animation Timer
static uint32_t boot_start_time = 0;

// 4. Helper Functions
void clear_board(void) {
    for (uint8_t r = 0; r < MINE_ROWS; r++) {
        for (uint8_t c = 0; c < MINE_COLS; c++) {
            game_board[r][c].is_mine = false;
            game_board[r][c].is_visible = false;
            game_board[r][c].is_flagged = false;
            game_board[r][c].neighbor_count = 0;
        }
    }
}

void generate_mines(uint8_t safe_r, uint8_t safe_c) {
    srand(timer_read()); 
    uint8_t mines_placed = 0;
    while (mines_placed < NUM_MINES) {
        uint8_t r = rand() % MINE_ROWS;
        uint8_t c = rand() % MINE_COLS;
        if (game_board[r][c].is_mine) continue;
        // Ensure first click is safe
        if (abs((int)r - (int)safe_r) <= 1 && abs((int)c - (int)safe_c) <= 1) continue;
        game_board[r][c].is_mine = true;
        mines_placed++;
    }
    // Calculate numbers
    for (uint8_t r = 0; r < MINE_ROWS; r++) {
        for (uint8_t c = 0; c < MINE_COLS; c++) {
            if (game_board[r][c].is_mine) continue;
            for (int8_t dr = -1; dr <= 1; dr++) {
                for (int8_t dc = -1; dc <= 1; dc++) {
                    int8_t nr = r + dr;
                    int8_t nc = c + dc;
                    if (nr >= 0 && nr < MINE_ROWS && nc >= 0 && nc < MINE_COLS) {
                        if (game_board[nr][nc].is_mine) game_board[r][c].neighbor_count++;
                    }
                }
            }
        }
    }
}

void init_game(void) {
    clear_board();
    game_status = STATUS_IDLE; 
    first_move = true;         
}

void check_win(void) {
    uint8_t safe_cells_hidden = 0;
    for (uint8_t r = 0; r < MINE_ROWS; r++) {
        for (uint8_t c = 0; c < MINE_COLS; c++) {
            if (!game_board[r][c].is_mine && !game_board[r][c].is_visible) safe_cells_hidden++;
        }
    }
    if (safe_cells_hidden == 0) game_status = STATUS_WON;
}

void reveal_cell(uint8_t r, uint8_t c) {
    if (r >= MINE_ROWS || c >= MINE_COLS) return;
    if (game_board[r][c].is_visible || game_board[r][c].is_flagged) return;
    
    game_board[r][c].is_visible = true;
    
    // Flood fill for empty cells
    if (game_board[r][c].neighbor_count == 0 && !game_board[r][c].is_mine) {
        for (int8_t dr = -1; dr <= 1; dr++) {
            for (int8_t dc = -1; dc <= 1; dc++) {
                if (dr == 0 && dc == 0) continue;
                reveal_cell(r + dr, c + dc);
            }
        }
    }
}

// ------------------------------------------------
// Standard QMK Functions
// ------------------------------------------------

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(0, 0, 150); 
    
    // Enter boot animation state on startup
    game_status = STATUS_BOOT;
    boot_start_time = timer_read32();
    clear_board();
}

// Main Rendering Loop
bool rgb_matrix_indicators_kb(void) {
    rgb_matrix_set_color_all(0, 0, 0); 

    // --- Boot Animation Logic ---
    if (game_status == STATUS_BOOT) {
        uint32_t elapsed = timer_elapsed32(boot_start_time);
        
        if (elapsed > 1600) {
            // Animation finished, ready to play
            game_status = STATUS_IDLE;
        } 
        else if (elapsed > 1300) {
            // 1.3s - 1.6s: Flash white (System Ready)
             for (uint8_t r = 0; r < MINE_ROWS; r++) {
                for (uint8_t c = 0; c < MINE_COLS; c++) {
                     rgb_matrix_set_color(led_map[r][c], 255, 255, 255);
                }
             }
        }
        else {
            // 0 - 1.3s: Row Scan (System Check)
            // Light up a new row every 300ms
            uint8_t active_rows = (elapsed / 300) + 1; 
            
            for (uint8_t r = 0; r < MINE_ROWS; r++) {
                if (r < active_rows) {
                    for (uint8_t c = 0; c < MINE_COLS; c++) {
                        // Use Cyan for sci-fi look
                        rgb_matrix_set_color(led_map[r][c], 0, 255, 255);
                    }
                }
            }
        }
        return true; // Skip game rendering during animation
    }

    // --- Game Rendering ---

    if (game_status == STATUS_WON) {
        // Flash green on win
        if ((timer_read() / 500) % 2 == 0) { 
             for (uint8_t r = 0; r < MINE_ROWS; r++) {
                for (uint8_t c = 0; c < MINE_COLS; c++) {
                     rgb_matrix_set_color(led_map[r][c], 0, 255, 0);
                }
             }
        }
        return true;
    }

    for (uint8_t r = 0; r < MINE_ROWS; r++) {
        for (uint8_t c = 0; c < MINE_COLS; c++) {
            uint8_t idx = led_map[r][c];
            Cell *cell = &game_board[r][c];

            if (game_status == STATUS_LOST) {
                if (cell->is_mine) {
                    rgb_matrix_set_color(idx, 255, 0, 0); // Red for mines
                } else if (cell->is_visible) {
                    rgb_matrix_set_color(idx, 50, 0, 0);  // Dim red for board
                }
                continue; 
            }

            if (cell->is_flagged) {
                rgb_matrix_set_color(idx, 255, 0, 100); // Pink for flags
            } else if (!cell->is_visible) {
                rgb_matrix_set_color(idx, 20, 20, 20);  // Dim white for hidden
            } else {
                if (cell->is_mine) {
                    rgb_matrix_set_color(idx, 255, 0, 0); 
                } else {
                    // Color code for numbers
                    switch (cell->neighbor_count) {
                        case 0: rgb_matrix_set_color(idx, 0, 0, 0); break;   
                        case 1: rgb_matrix_set_color(idx, 0, 0, 255); break; 
                        case 2: rgb_matrix_set_color(idx, 0, 255, 0); break; 
                        case 3: rgb_matrix_set_color(idx, 255, 255, 0); break; 
                        case 4: rgb_matrix_set_color(idx, 255, 128, 0); break; 
                        default: rgb_matrix_set_color(idx, 255, 0, 255); break; 
                    }
                }
            }
        }
    }
    return true;
}

// Key Processing
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

    // Block input during boot animation
    if (game_status == STATUS_BOOT) {
        return true; 
    }

    if (keycode == KC_SPC) {
        init_game(); // Reset game
        return false;
    }

    if (game_status == STATUS_WON || game_status == STATUS_LOST) return true; 

    for (uint8_t r = 0; r < MINE_ROWS; r++) {
        for (uint8_t c = 0; c < MINE_COLS; c++) {
            if (keycode == key_map[r][c]) {
                // Shift + Key to toggle Flag
                if (get_mods() & MOD_MASK_SHIFT) {
                    if (!game_board[r][c].is_visible) {
                        game_board[r][c].is_flagged = !game_board[r][c].is_flagged;
                    }
                } else {
                    if (!game_board[r][c].is_flagged) {
                        // First move safety mechanism
                        if (first_move) {
                            generate_mines(r, c); 
                            game_status = STATUS_PLAYING;
                            first_move = false;
                        }
                        
                        if (game_board[r][c].is_mine) {
                            game_board[r][c].is_visible = true;
                            game_status = STATUS_LOST; 
                        } else {
                            reveal_cell(r, c);
                            check_win(); 
                        }
                    }
                }
                return false; // Override default key behavior
            }
        }
    }
    return true;
}