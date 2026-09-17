# Mastering Tmux (Terminal Multiplexer)

`tmux` allows you to run multiple terminal sessions inside a single window, detach from them, and reattach later. It is invaluable for remote work (SSH) because if your connection drops, your tmux session (and any running scripts) stays alive.

## 1. Core Concepts
- **Server:** Runs in the background and manages everything.
- **Session:** A collection of Windows. You can detach/attach to Sessions.
- **Window:** Like a tab in a browser. Fills the whole screen.
- **Pane:** Windows can be split into multiple panes.

## 2. Basic Commands (From normal shell)

Start a new session:
```bash
tmux
# Or with a specific name:
tmux new -s my_session
```

List running sessions:
```bash
tmux ls
```

Attach to a running session:
```bash
tmux attach -t my_session
```

Kill a session:
```bash
tmux kill-session -t my_session
```

## 3. The Prefix Key

Inside tmux, all commands are preceded by the **Prefix** key combo.
By default, the Prefix is **`Ctrl+b`**.
*(You press Ctrl+b, release them, then press the command key).*

## 4. Navigating and Splitting Panes

- **`Prefix` + `%`** : Split pane vertically (left/right).
- **`Prefix` + `"`** : Split pane horizontally (top/bottom).
- **`Prefix` + `Arrow Keys`** : Navigate between panes.
- **`Prefix` + `z`** : Toggle pane "zoom" (make it fullscreen temporarily).
- **`Prefix` + `x`** : Close the current pane.
- **`Prefix` + `Hold Ctrl + Arrow Keys`** : Resize panes.

## 5. Managing Windows

- **`Prefix` + `c`** : Create a new window.
- **`Prefix` + `n`** : Go to the **N**ext window.
- **`Prefix` + `p`** : Go to the **P**revious window.
- **`Prefix` + `0..9`** : Go to a specific window by number.
- **`Prefix` + `,`** : Rename the current window.
- **`Prefix` + `w`** : List all windows and sessions (interactive).

## 6. Detaching

- **`Prefix` + `d`** : Detach from the session. The session keeps running in the background!

## 7. Customizing Tmux (`~/.tmux.conf`)

Tmux is highly customizable via `~/.tmux.conf`. After editing this file, reload it with `tmux source-file ~/.tmux.conf` or restart tmux.

A common customized `~/.tmux.conf`:
```tmux
# Remap prefix from 'C-b' to 'C-a' (easier to reach)
unbind C-b
set-option -g prefix C-a
bind-key C-a send-prefix

# Enable mouse mode (clickable windows, panes, resizable panes)
set -g mouse on

# Split panes using | and - (more intuitive than % and ")
bind | split-window -h
bind - split-window -v
unbind '"'
unbind %

# Reload config file easily
bind r source-file ~/.tmux.conf \; display-message "Config reloaded..."

# Start window and pane numbering at 1, not 0
set -g base-index 1
setw -g pane-base-index 1
```

## Exercises

**Exercise 1: Sessions**
Create a new tmux session named `hacking`. Inside it, run `top`. Detach from the session. Run `tmux ls` to see it. Reattach to it.

**Exercise 2: Panes**
Inside a session, split your window vertically. In the right pane, split it horizontally. You should have 3 panes. Try resizing them using `Ctrl+b` followed by holding `Ctrl` and pressing arrow keys.

**Exercise 3: Configuration**
Create a `~/.tmux.conf` file with the snippet above. Source it (`tmux source ~/.tmux.conf`). Verify that your prefix is now `Ctrl+a` and that you can use the mouse to click between panes.
