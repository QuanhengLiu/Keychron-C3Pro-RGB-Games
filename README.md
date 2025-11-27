# Interactive RGB Games on QMK Firmware

> A custom firmware project for the **Keychron C3 Pro**, featuring two interactive games implemented entirely through RGB lighting feedback and C-based logic.

---

## Project Demo

| ⚡ Reaction Time Test | 💣 RGB Minesweeper |
| :---: | :---: |
| ![Reaction Game Demo](https://github.com/user-attachments/assets/e95b40c9-6802-445c-b8ef-9b20e02e28fd)| ![Minesweeper Demo](https://github.com/user-attachments/assets/3dafee63-52c2-46ea-a1a4-4a3ee99063ae)|

---

## Hardware Specs

* **Device:** Keychron C3 Pro (RGB Version)
* **MCU:** High-performance ARM Cortex-M4 (STM32F401)
* **Firmware Base:** QMK Firmware
* **Key Mechanism:** Per-key RGB Matrix

---

## 🕹️ Game 1: Reaction Time Test

A reflex training game integrated directly into the keyboard. The keyboard waits for a random interval and flashes a signal; your goal is to press a key as quickly as possible. The RGB lighting will display your speed tier.

---

## 🕹️ Game 2: RGB Minesweeper

An embedded version of the classic Minesweeper logic, using the keyboard's switch matrix as the grid and RGB LEDs for status feedback.

### 1. Power On & Boot Sequence
When you plug in the keyboard, the system initiates a **Self-Check Sequence**:
1.  **Scanning**: Cyan lights scan the game area row by row.
2.  **System Ready**: The entire grid flashes **White** once.
3.  **Standby**: All lights turn off. The game is ready.

### 2. Game Controls

| Action | Key Combination | Description |
| :--- | :--- | :--- |
| **Reveal Cell** | Press any Game Key | Reveals the content of the cell. |
| **Flag Mine** | `Shift` + Game Key | Marks the cell as a mine (**Pink** light). |
| **Unflag** | `Shift` + Game Key | Removes the flag from a cell. |
| **Restart** | `Spacebar` | Resets the board and starts a new game immediately. |

### 3. The Game Area

The game uses a **4x6 Grid** on the left side of your keyboard:

* **Row 1:** `1`, `2`, `3`, `4`, `5`, `6`
* **Row 2:** `Q`, `W`, `E`, `R`, `T`, `Y`
* **Row 3:** `A`, `S`, `D`, `F`, `G`, `H`
* **Row 4:** `Z`, `X`, `C`, `V`, `B`, `N`

### 4. Color Legend (Visual Feedback)

| Color | Meaning |
| :--- | :--- |
| ⚪ **Gray** | Unknown / Hidden cell |
| 🔵 **Blue** | **1** mine nearby |
| 🟢 **Green** | **2** mines nearby |
| 🟡 **Yellow** | **3** mines nearby |
| 🟠 **Orange** | **4** mines nearby |
| 🌸 **Pink** | Flagged as Mine |
| 🔴 **Red** | **BOOM!** (Game Over) |

### 5. Special Features

* **First Click Safe:** Your very first click in a new game is guaranteed to be safe. It will automatically open up a starting area, so no luck is required to start.
* **Auto-Open:** Revealing a "0" (zero mines nearby) automatically reveals all connected empty cells to speed up gameplay.
* **Win Condition:** Reveal all safe cells to trigger the **Victory Light Show** (Flashing Green).
* **Lose Condition:** Hitting a mine triggers an explosion and reveals all hidden mines in **Red**.

---

## Code Structure

This repository contains the custom keymap and game logic source code.

* `keymap.c`: Contains the core game loops and key event handling (State Machine).
* `rgb_matrix_user.inc` (Optional): Custom RGB effect definitions.

---

## How to Build & Flash

1.  **Setup Environment:**
    Ensure you have the QMK build environment or [QMK Toolbox](https://github.com/qmk/qmk_toolbox) installed.
2.  **Clone Source:**
    Place this project folder into `qmk_firmware/keyboards/keychron/c3_pro/ansi/rgb/keymaps/`.
3.  **Compile:**
    ```bash
    qmk compile -kb keychron/c3_pro/ansi/rgb -km [YOUR_KEYMAP_NAME]
    ```
4.  **Flash:**
    Switch the keyboard to **DFU Mode** (Remove spacebar module to find the reset button or hold Esc while plugging in), then flash the `.bin` file using QMK Toolbox.

---

## License

This project is licensed under the [GPL-3.0](LICENSE) or later (Following QMK standards).
