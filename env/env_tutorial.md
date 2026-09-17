# Mastering the `env` Command

The `env` command is used to print the environment variables or to run another utility in an altered environment without having to modify the currently existing environment.

## 1. Viewing Environment Variables

Running `env` without any arguments simply prints all exported environment variables in the current shell session.

```bash
env
```

This is often used with `grep` (or `rg`) to find specific variables:

```bash
env | grep USER
```

## 2. Running a Command with a Modified Environment

The most powerful use of `env` is to temporarily set variables for a single command execution. This does not affect your current shell.

```bash
# Syntax: env [NAME=VALUE]... [COMMAND] [ARG]...
env MY_VAR="Hello World" bash -c 'echo $MY_VAR'
```

If you try to `echo $MY_VAR` after running the above, it will be empty because the variable only existed for that specific `bash` execution.

## 3. Ignoring the Current Environment

Sometimes you want to run a command in a pristine, empty environment to ensure it doesn't rely on existing configurations or to test how it behaves on a fresh system. Use the `-i` (ignore-environment) flag.

```bash
env -i bash -c 'env'
```
You will notice the output is drastically smaller, usually only containing `PWD` and `SHLVL`.

## 4. Unsetting Variables for a Command

You can remove a specific variable from the environment for the duration of a command using `-u`.

```bash
env -u PATH command_that_needs_no_path
```

## 5. Usage in Shebangs (`#!`)

You will often see `env` used in script shebangs.

```bash
#!/usr/bin/env python3
```

Instead of hardcoding `#!/usr/bin/python3` (which might fail if python3 is installed in `/usr/local/bin/python3`), using `env` tells the system to search the user's `$PATH` to find the `python3` executable.

---

## Exercises

**Exercise 1: Inspecting Environment**
Find out your current `HOME`, `USER`, and `SHELL` environment variables using `env` and `grep`.

**Exercise 2: Temporary Variable**
Write a 1-line command using `env` that runs `printenv MY_SECRET` with `MY_SECRET` temporarily set to `SuperSecretValue`. Verify that running `printenv MY_SECRET` normally afterward yields nothing.

**Exercise 3: The Blank Slate**
Run a new `bash` instance using `env -i bash`. Inside that new bash instance, type `echo $PATH`. What is the result? Why? Type `exit` to return to your normal shell.

**Exercise 4: Shebang Practice**
Create a small bash script `hello.sh` that prints "Hello". Use `env` in the shebang to resolve `bash`. Make it executable and run it.
