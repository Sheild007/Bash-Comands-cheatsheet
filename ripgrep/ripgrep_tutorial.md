# Mastering `rg` (ripgrep)

`ripgrep` (usually just `rg` in the terminal) is a line-oriented search tool that recursively searches your current directory for a regex pattern. By default, `ripgrep` respects your `.gitignore` and automatically skips hidden files/directories and binary files. It is extremely fast.

## 1. Basic Searching

The simplest way to use `rg` is to give it a string to search for:

```bash
rg "search_term"
```
This searches for "search_term" in the current directory and all subdirectories.

To search in a specific file or directory:
```bash
rg "search_term" path/to/dir_or_file
```

## 2. Case Sensitivity

By default, `rg` is case-sensitive. 

**Ignore Case:**
Use `-i` to ignore case entirely.
```bash
rg -i "error"
```

**Smart Case:**
Use `-S` for smart case. It ignores case if the search term is all lowercase, but becomes case-sensitive if you include uppercase letters.
```bash
rg -S "error" # matches Error, ERROR, error
rg -S "Error" # matches only Error
```

## 3. Viewing Context

Often you want to see the lines around your match.
- `-A NUM`: Print NUM lines **A**fter the match.
- `-B NUM`: Print NUM lines **B**efore the match.
- `-C NUM`: Print NUM lines of **C**ontext (before and after).

```bash
rg -C 3 "def main"
```

## 4. Filtering Files

You can restrict your search to specific file types or filenames.

**By File Type:**
Use `-t` (type). `rg` knows about many file types (e.g., `-t py` for Python, `-t js` for JavaScript).
```bash
rg "TODO" -t py
```

**Exclude File Type:**
Use `-T` to exclude a type.
```bash
rg "TODO" -T html
```

**By Glob (Filename Pattern):**
Use `-g` to specify a glob pattern.
```bash
rg "function" -g "*.config.js"
```

## 5. Showing File Names Only

If you only want a list of files that contain the match, use `-l` (files-with-matches).
```bash
rg -l "console.log"
```

## 6. Regex Searching

`rg` uses Rust's regex engine. You can pass regular expressions directly.
```bash
# Match 'word', 'ward', 'weird', etc.
rg "w.*rd"

# Match whole words only
rg -w "the"
```

## Exercises

**Exercise 1: Basic Search**
Search for the word `bash` in all files in the current directory.

**Exercise 2: Smart Case & Context**
Search for `export` using smart-case (`-S`), and print 2 lines of context (`-C 2`) around each match.

**Exercise 3: Filtering**
Find all instances of the word `TODO` but ONLY in `.md` or markdown files (hint: use `-t md`).

**Exercise 4: Counting**
Use `rg -c "pattern"` to count the number of matching lines per file. Find out how many times the word `the` (case-insensitive) appears in your markdown files.
