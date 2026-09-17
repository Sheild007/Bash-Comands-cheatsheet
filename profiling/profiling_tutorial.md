# Profiling and System Tracing

When a program is slow, crashing inexplicably, or consuming too much memory, standard debuggers aren't always the best tool. You need to look at **how** it interacts with the OS, memory, and CPU.

First, compile our exercise program with debug symbols so our profilers know the function names:
```bash
gcc -g leaky_cpu_hog.c -o leaky
```

---

## 1. `strace` (System Call Tracer)

Every time a program wants to read a file, allocate memory, or send network data, it asks the Operating System via a **System Call**. `strace` logs every single system call your program makes.

**Basic trace:**
```bash
strace ./leaky
```
*This dumps thousands of lines showing the program talking to the Linux kernel.*

**Summary Mode (Incredibly Useful):**
To see *which* syscalls are taking the most time:
```bash
strace -c ./leaky
```

**Filter by System Call:**
If you only care about files being opened:
```bash
strace -e openat,read,write ./leaky
```

---

## 2. `valgrind` 

`valgrind` is actually a suite of tools. It simulates the CPU, tracking every single memory allocation and instruction. It is slow, but highly accurate.

### 2a. Memcheck (Memory Leaks and Errors)
By default, Valgrind runs `memcheck`. It finds memory leaks (missing `free()`), uninitialized memory usage, and out-of-bounds reads/writes.

```bash
valgrind --leak-check=full --track-origins=yes ./leaky
```
*Look for the "HEAP SUMMARY" and "LEAK SUMMARY" at the bottom!*

### 2b. Callgrind (Profiling)
Callgrind profiles your code, tracking function calls, execution counts, and instruction costs.

```bash
valgrind --tool=callgrind ./leaky
```
This generates a file named `callgrind.out.<pid>`. You can view it graphically using a tool like **KCachegrind** (or **QCachegrind**), which provides an amazing visual map of where your program spends its time.

---

## 3. `perf` (Linux Performance Analyzer)

Unlike Valgrind which simulates execution, `perf` reads hardware performance counters directly from your CPU. It is extremely fast and has very low overhead, making it safe for production systems.

**Stat Summary:**
Get a high-level overview of CPU cycles, instructions, and cache misses:
```bash
perf stat ./leaky
```

**Record and Report:**
To see exactly *which functions* are eating your CPU, you sample the execution at a high frequency.

```bash
# 1. Record the execution graph (-g enables call graphs)
perf record -g ./leaky

# 2. View an interactive text-based report
perf report
```
*(In the report, you can expand functions to see exactly who called what).*

---

## 4. Flame Graphs

Flame Graphs (invented by Brendan Gregg) are the industry standard for visualizing performance data. They take the output of `perf` and turn it into a beautiful, interactive SVG image.

*Note: You need to clone the [FlameGraph repository](https://github.com/brendangregg/FlameGraph) to get the scripts.*

**How to generate a Flame Graph from `perf`:**
```bash
# 1. Record the data
perf record -F 99 -g -- ./leaky

# 2. Dump the data to text
perf script > out.perf

# 3. Fold the stacks (using Brendan Gregg's script)
./FlameGraph/stackcollapse-perf.pl out.perf > out.folded

# 4. Render the SVG
./FlameGraph/flamegraph.pl out.folded > profile.svg
```
Open `profile.svg` in any web browser. 
- The **x-axis** represents CPU time (wider = takes more time).
- The **y-axis** represents the call stack (functions calling functions).
- You can click on blocks to zoom in!

---

## Exercises

**Exercise 1: `strace` Summary**
Run `strace -c ./leaky`. Look at the table. Which system call was executed the most times? (Hint: It should be `write` or `openat` due to our `lots_of_syscalls` function).

**Exercise 2: Finding the Leak**
Run `valgrind --leak-check=full ./leaky`. 
Scroll through the output. It will tell you exactly how many bytes were leaked, and the exact function (`leak_memory`) and line number where the `malloc` occurred! Go fix the leak in `leaky_cpu_hog.c` by adding `free(leaked_array)` at the end of the function.

**Exercise 3: `perf` Profiling**
Run `perf record -g ./leaky`, then run `perf report`. Find the function taking up ~99% of the CPU time. (It will be `do_heavy_work`).

**Exercise 4: Render a Flame Graph (Challenge)**
1. Clone the repo: `git clone https://github.com/brendangregg/FlameGraph`
2. Follow the 4 steps in the Flame Graph section above to generate `profile.svg`.
3. Open `profile.svg` in a browser and click around!
