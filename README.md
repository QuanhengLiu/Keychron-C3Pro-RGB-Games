# Keychron-C3Pro-RGB-Games
Embedded C projects based on QMK firmware: RGB Minesweeper &amp; Reaction Time Test running on Keychron C3 Pro.
# Interactive RGB Games on QMK Firmware

> A custom firmware project for the **Keychron C3 Pro**, featuring two interactive games implemented entirely through RGB lighting feedback and C-based logic.

---

## 🎮 Project Demo

| ⚡ Reaction Time Test | 💣 RGB Minesweeper |
| :---: | :---: |
| ![Reaction Game Demo](https://github.com/user-attachments/assets/e95b40c9-6802-445c-b8ef-9b20e02e28fd)| ![Minesweeper Demo](https://github.com/user-attachments/assets/3dafee63-52c2-46ea-a1a4-4a3ee99063ae)|

---

## ⌨️ Hardware Specs

* **Device:** Keychron C3 Pro (RGB Version)
* **MCU:** High-performance ARM Cortex-M4 (STM32F401)
* **Firmware Base:** QMK Firmware
* **Key Mechanism:** Per-key RGB Matrix

---

## ✨ Game Features

### 1. Reaction Time Test ⚡
A reflex training game integrated directly into the keyboard.

### 2. RGB Minesweeper 💣
##  Power On & Boot Sequence
[cite_start]When you plug in the keyboard, the system initiates a **Self-Check Sequence**[cite: 4]:
1.  [cite_start]**Scanning**: Cyan lights scan the game area row by row[cite: 4].
2.  [cite_start]**System Ready**: The entire grid flashes **White** once[cite: 5].
3.  **Standby**: All lights turn off. [cite_start]The game is ready[cite: 5].

---

## 🎮 Game Controls

| Action | Key Combination | Description |
| :--- | :--- | :--- |
| **Reveal Cell** | Press any Game Key | [cite_start]Reveals the content of the cell[cite: 7]. |
| **Flag Mine** | `Shift` + Game Key | [cite_start]Marks the cell as a mine (**Pink** light)[cite: 7]. |
| **Unflag** | `Shift` + Game Key | [cite_start]Removes the flag from a cell[cite: 7]. |
| **Restart** | `Spacebar` | [cite_start]Resets the board and starts a new game immediately[cite: 7]. |

---

## 🗺️ The Game Area

[cite_start]The game uses a **4x6 Grid** on the left side of your keyboard[cite: 8, 9]:

* [cite_start]**Row 1:** `1`, `2`, `3`, `4`, `5`, `6` [cite: 10]
* [cite_start]**Row 2:** `Q`, `W`, `E`, `R`, `T`, `Y` [cite: 11]
* [cite_start]**Row 3:** `A`, `S`, `D`, `F`, `G`, `H` [cite: 12]
* [cite_start]**Row 4:** `Z`, `X`, `C`, `V`, `B`, `N` [cite: 13]

---

## 🎨 Color Legend (Visual Feedback)

| Color | Meaning |
| :--- | :--- |
| ⚪ **Gray** | [cite_start]Unknown / Hidden cell [cite: 15] |
| 🔵 **Blue** | [cite_start]**1** mine nearby [cite: 16] |
| 🟢 **Green** | [cite_start]**2** mines nearby [cite: 17] |
| 🟡 **Yellow** | [cite_start]**3** mines nearby [cite: 18] |
| 🟠 **Orange** | [cite_start]**4** mines nearby [cite: 19] |
| 🌸 **Pink** | [cite_start]Flagged as Mine [cite: 20] |
| 🔴 **Red** | [cite_start]**BOOM!** (Game Over) [cite: 21] |

---

## ✨ Game Features

### 1. First Click Safe
Your very first click in a new game is guaranteed to be safe. [cite_start]It will automatically open up a starting area, so no luck is required to start[cite: 23, 24].

### 2. Auto-Open
[cite_start]Revealing a "0" (zero mines nearby) automatically reveals all connected empty cells to speed up gameplay[cite: 25].

### 3. Win Condition
[cite_start]Reveal all safe cells to trigger the **Victory Light Show** (Flashing Green)[cite: 26].

### 4. Lose Condition
[cite_start]Hitting a mine triggers an explosion and reveals all hidden mines in **Red**[cite: 27].

---

## 🛠️ Code Structure

This repository contains the custom keymap and game logic source code.

* `keymap.c`: Contains the core game loops and key event handling (State Machine).

---

## 🚀 How to Build & Flash

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

## 📄 License

This project is licensed under the [GPL-3.0](LICENSE) or later (Following QMK standards).
