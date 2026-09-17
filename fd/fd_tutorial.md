# Mastering `fd`

`fd` is a modern, fast, and user-friendly alternative to the traditional `find` command. Like `rg` (ripgrep), it is written in Rust, extremely fast, and respects your `.gitignore` files by default. 

*Note: On some systems (like Debian/Ubuntu), the command is installed as `fdfind` to avoid clashing with another package, but it's usually aliased to `fd`.*

## 1. Basic Searching

To search for a file or directory by name, just type `fd` followed by a pattern.

```bash
# Search for files containing 'tutorial' in the name
fd tutorial
```

By default, `fd` uses a smart-case search: it is case-insensitive unless your search term contains an uppercase letter.

## 2. Searching by Extension

One of the most common tasks is finding files of a specific type. `fd` makes this incredibly easy with the `-e` (extension) flag.

```bash
# Find all markdown files
fd -e md

# Find all python and javascript files
fd -e py -e js
```

## 3. Filtering by Type

Use the `-t` (type) flag to restrict your search to files, directories, symlinks, etc.

- `-t f` : **f**iles
- `-t d` : **d**irectories
- `-t l` : sym**l**inks

```bash
# Find all directories containing the word 'exercises'
fd -t d exercises
```

## 4. Hidden and Ignored Files

Because `fd` respects `.gitignore` and skips hidden files/folders (like `.git` or `.ssh`) by default, you sometimes need to tell it to look everywhere.

- `-H` (or `--hidden`): Search hidden files and directories.
- `-I` (or `--no-ignore`): Do not respect `.gitignore` rules.
- `-u` (or `--unrestricted`): Alias for `-H -I`. Do it twice (`-uu`) to also search `.git/`.

```bash
# Find a hidden config file
fd -H ".bashrc"
```

## 5. Command Execution (Like `find -exec`)

`fd` can execute a command on every file it finds.
- `-x` executes the command *once for each file* (in parallel).
- `-X` executes the command *once with all files* passed as arguments.

In the command, `{}` is replaced by the file path.

```bash
# Change permissions on all .sh files
fd -e sh -x chmod +x {}

# Delete all .tmp files (prompts once for all files)
fd -e tmp -X rm -i
```

## 6. Using Regular Expressions

`fd` uses regex by default for its search patterns.

```bash
# Find files starting with 'a' and ending with '.md'
fd '^a.*\.md$'
```
*(If you just want an exact string match instead of regex, use the `-g` flag for globbing, or `-F` for fixed strings).*

---

## Exercises

**Exercise 1: Basic Search**
Run `fd` without any arguments to see how it quickly lists every file in the current directory tree (excluding `.git` and ignores).

**Exercise 2: Finding Directories**
Use `fd` to find all directories (`-t d`) in your `shell 101` folder.

**Exercise 3: Extension Search**
Find all `.sh` scripts in your repository using the `-e` flag.

**Exercise 4: Execution**
Create a few temporary files: `touch a.tmp b.tmp c.tmp`. Use `fd` with the `-e tmp` flag and the `-X` flag to delete them all at once using `rm`. (e.g., `fd ... -X rm`).
