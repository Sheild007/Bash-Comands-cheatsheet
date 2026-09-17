# Mastering Unix Signals

Signals are a form of inter-process communication used in Unix-like systems. They are asynchronous notifications sent to a process to notify it of an event (like a user pressing Ctrl+C or a request to shut down).

## 1. The Important Signals

Every signal has an integer ID and a name.

- **`SIGINT` (2) - Interrupt:** Sent when the user types `Ctrl+C`. This is a request to terminate gracefully. Programs can catch this signal to clean up before exiting.
- **`SIGQUIT` (3) - Quit:** Sent when the user types `Ctrl+\`. Like SIGINT, but usually forces the process to produce a core dump for debugging.
- **`SIGKILL` (9) - Kill:** Forces the process to terminate immediately. **This cannot be caught, blocked, or ignored by the process.** Use this as a last resort if a program is completely frozen.
- **`SIGTERM` (15) - Terminate:** The default signal sent by the `kill` command. It is a polite request to terminate. The process is given a chance to save state, close files, and exit cleanly.
- **`SIGSTOP` (19) - Stop:** Pauses (freezes) a process immediately. It cannot be caught or ignored.
- **`SIGCONT` (18) - Continue:** Resumes a process that was paused by `SIGSTOP`.
- **`SIGHUP` (1) - Hangup:** Historically sent when a terminal connection was lost (e.g., modem hung up). Today, it is commonly used to tell daemon processes (like Nginx or SSHD) to **reload their configuration files** without restarting completely.

## 2. Sending Signals

### Using `kill` (By PID)
Despite the name, `kill` just sends signals (defaulting to SIGTERM / 15).
```bash
# Send SIGTERM (15)
kill 1234

# Send SIGKILL (9)
kill -9 1234
# OR
kill -SIGKILL 1234

# Send SIGHUP (1)
kill -HUP 1234
```

### Using `killall` (By Name)
Sends a signal to all processes matching a specific name.
```bash
killall -9 firefox
```

### Using `pkill` (By Pattern)
More powerful than `killall`, allows regex and other filtering.
```bash
# Kill processes matching "node"
pkill -f "node server.js"
```

## 3. Keyboard Shortcuts

Your terminal translates certain keystrokes into signals sent to the foreground process:
- **`Ctrl+C`**: Sends `SIGINT`.
- **`Ctrl+\`**: Sends `SIGQUIT`.
- **`Ctrl+Z`**: Sends `SIGTSTP` (Terminal Stop - similar to SIGSTOP but can be caught/ignored). You can then use the `bg` command to run the stopped job in the background, or `fg` to bring it back.

## 4. Trapping Signals in Bash (`trap`)

In bash scripts, you can use the `trap` command to execute code when a specific signal is received. This is crucial for cleanup (e.g., deleting temporary files if the user hits Ctrl+C).

**Syntax:** `trap 'commands' SIGNAL`

**Example Script (`cleanup.sh`):**
```bash
#!/bin/bash

# Create a temporary file
TEMP_FILE=$(mktemp)
echo "Created temp file: $TEMP_FILE"

# Define the trap: Remove the file if we exit normally OR get SIGINT/SIGTERM
trap 'echo "Cleaning up..."; rm -f "$TEMP_FILE"; exit' EXIT SIGINT SIGTERM

echo "Doing some work... press Ctrl+C to abort."
sleep 10
echo "Work finished!"
```
If you run this and press `Ctrl+C` while it is sleeping, the trap catches the `SIGINT`, runs the cleanup code, and exits.

## Exercises

**Exercise 1: Stop and Go**
Run a long process, like `sleep 1000`. Press `Ctrl+Z` to stop it. Run `jobs` to see it. Bring it back to the foreground with `fg`, then kill it with `Ctrl+C`.

**Exercise 2: Sending HUP**
If you have a background service (or even just another terminal running `sleep 10000`), find its PID using `ps aux | grep sleep`. Send it a `SIGHUP` using `kill -HUP <PID>`. (For `sleep`, it will just terminate).

**Exercise 3: Trapping**
Create the `cleanup.sh` script above, make it executable, run it, and interrupt it with `Ctrl+C`. Verify that it prints "Cleaning up..." before exiting.
