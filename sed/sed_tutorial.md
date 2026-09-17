# Sed (Stream Editor) Tutorial

`sed` is used to perform basic text transformations on an input stream (a file or input from a pipeline). It is most commonly used for finding and replacing text.

## Basic Syntax
`sed [OPTIONS] 'script' filename`

## Key Concepts (Substitution)
The `s` command (substitute) is the most common:
`sed 's/search_pattern/replacement_string/flags' file.txt`

- `g` flag : Global replacement (replace ALL occurrences on a line, not just the first).
- `i` or `I` flag : Case-insensitive matching.
- `-i` option : In-place editing (saves the changes directly to the file). Without this, `sed` just prints to the terminal.
- `-E` option : Use Extended Regular Expressions.

## Advanced Concepts
- `d` command : Delete lines. (e.g., `sed '3d' file.txt` deletes line 3; `sed '/pattern/d' file.txt` deletes lines containing pattern).
- `p` command : Print lines. Usually used with `-n` (which suppresses default printing). e.g., `sed -n '1,5p' file.txt` prints lines 1 to 5.
- `&` character : In the replacement string, `&` represents the matched text. (e.g., `s/[0-9]*/[&]/` puts brackets around numbers).
- Capture groups : Like in regex, `\(group\)` captures text, referenced by `\1`, `\2` in the replacement. (With `-E`, you can just use `(group)`).

---

## Exercises (Use `legacy_code.txt`)

1. **Replace all occurrences of "foo" with "bar"**. (Print to screen).
2. **Replace "foo" with "bar" GLOBALLY on every line**.
3. **Delete the line that contains the word "DEPRECATED"**.
4. **Remove all leading spaces/tabs from the lines.** (Hint: Use `s/^[ \t]*//`).
5. **Use capturing groups and `-E` to change the date format from `MM/DD/YYYY` to `YYYY-MM-DD`**.
6. **Once you have a working command, use the `-i` flag to save your changes to the file.**
