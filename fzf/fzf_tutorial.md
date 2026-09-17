# Mastering `fzf` (Fuzzy Finder)

`fzf` is a general-purpose command-line fuzzy finder. It is an interactive filter program for any kind of list (files, command history, processes, hostnames, bookmarks, git commits, etc.).

## 1. The Core Concept

At its heart, `fzf` just reads a list of items from standard input (stdin), lets you interactively pick one by typing a few letters, and then prints your selection to standard output (stdout).

```bash
# Type some words, fzf will let you pick one, and it will echo your choice!
echo -e "apple\nbanana\ncherry" | fzf
```

## 2. Using `fzf` with Commands

Since `fzf` prints the chosen item, you can use command substitution `$()` to pass that item into another command.

**Open a file in your editor:**
```bash
# Finds all files in the current directory, lets you pick one, then vim opens it.
vim $(fzf)
```

**Kill a process interactively:**
```bash
# Lists processes, lets you fuzzy search for the one to kill.
kill -9 $(ps -ef | fzf | awk '{print $2}')
```

## 3. Shell Integration (The Best Part!)

When `fzf` is installed, it comes with default shell keybindings that will change your life:

- **`CTRL-T` (Find Files):** Press `CTRL-T` in your terminal. It will open `fzf` with a list of files in the current directory. When you select one, it pastes the file path directly into your current command line!
- **`CTRL-R` (Command History):** Instead of standard reverse-i-search, pressing `CTRL-R` opens your entire shell history in `fzf`. Type a few characters to instantly find that long, complex command you ran 3 weeks ago.
- **`ALT-C` (Change Directory):** Opens `fzf` with a list of subdirectories. Pick one, and your shell instantly `cd`s into it!

*(Note: Depending on how you installed `fzf`, you might need to manually enable these bindings in your `.bashrc` or `.zshrc` by sourcing the fzf keybindings file).*

## 4. Previews

You can configure `fzf` to show a live preview of the currently highlighted item using the `--preview` flag.

```bash
# Browse files and see their contents on the right side!
fzf --preview 'cat {}'

# If you have `bat` installed (a better cat), it's even prettier:
fzf --preview 'bat --color=always {}'
```
*(In the preview command, `{}` is a placeholder for the currently highlighted item).*

## 5. Multi-Selection

Use the `-m` (or `--multi`) flag to allow selecting multiple items. Use `TAB` to select/deselect items, and `ENTER` to confirm.

```bash
# Pick multiple files and delete them
rm -i $(fzf -m)
```

---

## Exercises

**Exercise 1: Basic Piping**
Run `ls | fzf`. Type a few letters of a file that exists in your directory, hit enter, and see what happens.

**Exercise 2: Interactive Editing**
Run `nano $(fzf)` (or replace `nano` with your favorite editor). Select a file. Notice how it immediately opens that file. 

**Exercise 3: Try the Keybindings**
In your terminal prompt, type `cat ` (with a trailing space), then press `CTRL-T`. Pick a file. See how the path gets inserted? Now hit enter to run the command.

**Exercise 4: History Search**
Press `CTRL-R` and search for the `awk` or `jq` commands you ran earlier today. 

**Exercise 5: The Preview Window**
Run the preview command: `fzf --preview 'cat {}'`. Use your up/down arrow keys to scroll through the files and watch the preview window update on the right side.
