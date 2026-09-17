# Debugging with GDB and RR

When dealing with compiled languages like C or C++, standard `print` statements aren't always enough to find bugs. You need powerful debuggers.

## 1. Preparation

To debug a program, you **must** compile it with debugging symbols enabled. Use the `-g` flag with `gcc` or `g++`.

```bash
# Compile our broken program with debug symbols
gcc -g buggy.c -o buggy
```

## 2. GDB (GNU Debugger)

`gdb` allows you to inspect what a program is doing while it executes, or what it was doing at the moment it crashed.

**Starting GDB:**
```bash
gdb ./buggy
```

**Common GDB Commands:**
- `run` (or `r`): Start executing the program.
- `break <line_number>` (or `b 10`): Set a breakpoint at line 10. Execution will pause when it reaches this line.
- `break <function>` (or `b main`): Set a breakpoint at the start of a function.
- `continue` (or `c`): Resume execution until the next breakpoint or crash.
- `next` (or `n`): Execute the next line of code (steps *over* functions).
- `step` (or `s`): Execute the next line of code (steps *into* functions).
- `print <variable>` (or `p sum`): Print the current value of a variable.
- `backtrace` (or `bt`): Print a trace of how you got to the current point (very useful when it crashes!).
- `quit` (or `q`): Exit GDB.

## 3. RR (Record and Replay)

`rr` (by Mozilla) is a revolutionary debugger that takes GDB to the next level. It allows you to **record** a program's execution once, and then **replay** it infinitely. More importantly, it supports **reverse debugging** (stepping backwards in time!).

*Note: `rr` requires Linux and specific CPU features. It usually won't work inside a standard Docker container or VM without special flags.*

**Recording Execution:**
```bash
rr record ./buggy
```
This runs the program and saves a trace to disk. If the bug is intermittent, you just run it in a loop until it crashes, record that specific crash, and you have it captured forever!

**Replaying the Record:**
```bash
rr replay
```
This drops you into a GDB session, but you are now inspecting the recorded past.

**Reverse Debugging Commands (RR specific):**
- `reverse-next` (or `rn`): Step backwards to the previous line.
- `reverse-step` (or `rs`): Step backwards into a function.
- `reverse-continue` (or `rc`): Run backwards until a breakpoint is hit.

This is magical: if a variable has a bad value on line 50, you can put a watchpoint on it (`watch variable`) and type `rc` to run backwards to find exactly when and where it was corrupted!

---

## Exercises

We have provided a intentionally broken C program called `buggy.c` in this directory. 

**Exercise 1: Basic GDB Crash Analysis**
1. Compile the program: `gcc -g buggy.c -o buggy`
2. Run it normally (`./buggy`). It will output a weird sum and then crash with a `Segmentation fault (core dumped)`.
3. Run it inside GDB: `gdb ./buggy`
4. Type `run`. Wait for it to crash. 
5. Type `backtrace` to see exactly what line caused the crash. 
6. Type `print ptr` to see the value of the pointer that caused it.

**Exercise 2: Finding the Logic Bug**
The sum printed is completely wrong (it should be 150, but it prints some random garbage memory). 
1. Open `buggy.c` in vim and fix the Segmentation Fault (Bug 2) by removing or commenting out the pointer lines, then recompile it.
2. Open GDB again. Put a breakpoint on the `for` loop (e.g., `b 9`).
3. Run the program. When it stops, type `print i` and `print sum`.
4. Type `continue` a few times to watch `i` increment. 
5. What happens when `i` reaches 5? Notice how it keeps reading memory past the end of `arr`! Fix the bug in `buggy.c`.

**Exercise 3: RR Magic (If your system supports it)**
1. Record the execution: `rr record ./buggy`
2. Replay it: `rr replay`
3. Type `continue` to let it crash.
4. Type `reverse-next` to step backwards in time right before the crash happened! 
