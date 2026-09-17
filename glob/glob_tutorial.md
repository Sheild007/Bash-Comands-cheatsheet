# Glob Patterns Tutorial

Glob patterns are used by the shell (like bash) to match filenames. They are NOT the same as Regular Expressions, though they look similar. 

## Key Concepts

- `*` : Matches 0 or more of ANY character.
  - `*.txt` matches all files ending in `.txt`.
  - `data*` matches all files starting with `data`.
- `?` : Matches exactly ONE character.
  - `file?.txt` matches `file1.txt`, `fileA.txt`, but not `file12.txt`.
- `[abc]` : Matches any one character in the brackets.
  - `script[123].sh` matches `script1.sh`, `script2.sh`, `script3.sh`.
- `[a-z]` : Matches ranges of characters.
- `[^abc]` or `[!abc]` : Matches any character NOT in the brackets.
- `{string1,string2}` : Brace expansion. (e.g., `cp file.{txt,bak}` expands to `cp file.txt file.bak`).

*Note: Globs usually don't match hidden files (starting with `.`) unless explicitly specified.*

---

## Exercises (Use `ls`, `echo`, or `find` in the `glob` directory)

1. **List all `.txt` files in the `docs/` directory**:
2. **List all files in `images/` that are either `.jpg` or `.png`**:
   *Hint: Use brace expansion or a wildcard.*
3. **List all Python scripts (`.py`) in `scripts/`**:
4. **List all files that start with `file` and end with a single character**:
   *Hint: Use `?`.*
5. **List the hidden configuration file**:
   *Hint: Wildcards don't match hidden files by default.*
6. **Use brace expansion to create three new files at once:** `touch {a,b,c}.log`
