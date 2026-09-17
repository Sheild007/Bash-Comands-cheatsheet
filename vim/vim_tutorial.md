# Mastering Vim

Vim is a highly configurable text editor built to make creating and changing text highly efficient. It operates heavily on **Modes**. Understanding modes is the key to mastering Vim.

## 1. The Four Primary Modes

- **Normal Mode:** This is where you spend most of your time. You don't type text here; you press keys to execute commands (move, delete, copy, paste). Press `Esc` to return to Normal Mode from anywhere.
- **Insert Mode:** Used for typing text. (Enter by pressing `i`, `a`, `o`, etc.).
- **Visual Mode:** Used for selecting text (like highlighting with a mouse). (Enter by pressing `v`).
- **Command-Line Mode:** Used for saving, exiting, and complex operations. (Enter by pressing `:` from Normal mode).

## 2. Moving Around (Normal Mode)

Forget the arrow keys! Keep your fingers on the home row.

**Basic Movement:**
- `h`: Left
- `j`: Down
- `k`: Up
- `l`: Right

**Word Movement:**
- `w`: Jump forward to the start of a word.
- `e`: Jump forward to the end of a word.
- `b`: Jump backward to the start of a word.

**Line & File Movement:**
- `0`: Jump to the start of the line.
- `$`: Jump to the end of the line.
- `gg`: Jump to the top of the file.
- `G`: Jump to the bottom of the file.
- `50G`: Jump to line 50.

## 3. Entering Insert Mode

Different ways to start typing:
- `i`: Insert *before* the cursor.
- `I`: Insert at the *beginning* of the line.
- `a`: Append *after* the cursor.
- `A`: Append at the *end* of the line.
- `o`: Open a *new line below* the cursor and insert.
- `O`: Open a *new line above* the cursor and insert.

## 4. Deleting, Copying, and Pasting (Normal Mode)

Vim calls copying "yanking" (`y`) and deleting/cutting "deleting" (`d`).

- `x`: Delete the character under the cursor.
- `dw`: Delete from cursor to the end of the word.
- `dd`: Delete the entire line.
- `3dd`: Delete 3 lines.
- `d$`: Delete from cursor to the end of the line.

- `yy`: Yank (copy) the entire line.
- `yw`: Yank word.
- `p`: Paste *after* the cursor.
- `P`: Paste *before* the cursor.

## 5. The "Change" Operator

The `c` command deletes text and immediately drops you into Insert Mode. It is incredibly powerful.
- `cw`: Change word (deletes word, enters insert mode).
- `cc`: Change the whole line.
- `c$`: Change to the end of the line.

## 6. Undo and Redo

- `u`: Undo the last change.
- `Ctrl + r`: Redo the last undone change.

## 7. Visual Mode (Selecting Text)

- `v`: Character-wise visual mode. Use movement keys (`h,j,k,l,w`) to highlight text, then press `d` to delete or `y` to yank.
- `V`: Line-wise visual mode (selects whole lines).
- `Ctrl + v`: Block visual mode (selects columns of text—great for commenting multiple lines).

## 8. Search and Replace

**Searching:**
- `/pattern`: Search forward for "pattern".
- `?pattern`: Search backward.
- `n`: Jump to next match.
- `N`: Jump to previous match.

**Replacing (Command-Line Mode):**
- `:%s/old/new/g`: Replace 'old' with 'new' globally across the whole file.
- `:s/old/new/g`: Replace on the current line only.

## 9. Saving and Exiting

Press `:` from Normal Mode:
- `:w` : Write (save).
- `:q` : Quit.
- `:wq` (or `:x` or `ZZ`): Save and quit.
- `:q!` : Quit WITHOUT saving.

---

## Exercises

**Exercise 1: Basic Movement**
Open a long file (`vim ~/.bashrc`). Do not use arrow keys. Move down 5 lines using `j`, move to the end of the line using `$`, and jump to the top using `gg`.

**Exercise 2: Delete and Paste**
In Vim, type `dd` on a line you don't need to delete it. Then type `p` to paste it back somewhere else. (Remember, deleting in Vim also cuts).

**Exercise 3: The Change Command**
Move your cursor to the beginning of a word. Type `cw`, type a new word, and press `Esc`.

**Exercise 4: Block Selection**
Type 3 lines of text. Move to the first character of the first line. Press `Ctrl + v` to enter block visual mode. Press `j` twice to go down two lines. Press `I` (Shift+i). Type `# ` to make a comment, then press `Esc`. All 3 lines will instantly be commented out!

**Exercise 5: Search and Replace**
Open a file, type `:%s/a/APPLE/g`, and press enter. Watch every 'a' turn into 'APPLE'. Undo it by pressing `u` in normal mode.
