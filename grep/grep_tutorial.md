# Grep (Global Regular Expression Print) Tutorial

`grep` searches text for lines matching a pattern and prints them.

## Basic Syntax
`grep [OPTIONS] "pattern" filename`

## Key Options
- `-i` : Ignore case (matches "Error", "error", "ERROR").
- `-v` : Invert match (prints lines that DO NOT match the pattern).
- `-c` : Count the number of matching lines.
- `-n` : Show line numbers alongside matching lines.
- `-r` or `-R` : Search recursively through directories.
- `-l` : Print only the names of files containing matches, not the matching lines.
- `-E` : Use Extended Regular Expressions (allows `+`, `?`, `|`, `()`).
- `-A num`, `-B num`, `-C num` : Print `num` lines After, Before, or around (Context) the match.
- `-o` : Print only the matched parts of a matching line, not the entire line.

---

## Exercises (Use `server_logs.txt`)

1. **Find all lines containing the word "ERROR" (case-insensitive)**.
2. **Count how many "INFO" messages are in the log**.
3. **Find all lines that DO NOT contain "DEBUG"**.
4. **Find "WARNING" messages and show the line numbers**.
5. **Find the IP address `192.168.1.50` and print the 2 lines BEFORE it** (`-B 2`).
6. **Use Extended Grep (`-E`) to find lines containing either "CRITICAL" or "ERROR"**.
7. **Extract ONLY the IP addresses from the file** (using `-o` and a regex for IPs).
