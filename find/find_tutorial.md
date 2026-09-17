# Find Tutorial

`find` is a powerful tool to search for files and directories in a directory hierarchy based on attributes like name, size, type, or time.

## Basic Syntax
`find [path] [expression]`

## Key Options & Expressions
- `-name "pattern"` : Search by filename (use quotes for globs like `*.c`).
- `-iname "pattern"` : Case-insensitive name search.
- `-type f` (file), `-type d` (directory) : Search by file type.
- `-size +10M` : Find files larger than 10 Megabytes (`k` for kb, `G` for GB). `-10M` means smaller.
- `-mtime -7` : Modified within the last 7 days (`+7` is older than 7 days).
- `-user username` : Find files owned by a specific user.
- `-perm 644` : Find files with exact permissions.
- `-empty` : Find empty files and directories.
- `-delete` : Delete the files that are found (CAREFUL!).
- `-exec command {} +` or `-exec command {} \;` : Execute a command on the found files. (`{}` is replaced by the filename).

---

## Exercises (Use the `find/` directory)

*Run these from the `/home/usmandauna/Documents/JOB interview prep/shell 101/find/` directory.*

1. **Find all `.c` files anywhere in the `project/` directory.**
2. **Find all directories (`-type d`) inside the `find/` directory.**
3. **Find files larger than 5MB.** (Should find `large_file.bin`).
4. **Find all empty files.** (Since we used `touch`, most files are empty!)
5. **Find files named `readme.txt` (case-insensitive) and print their locations.**
6. **Find all `.bak` files and use `-exec` to remove (`rm`) them.**
   *Command structure: `find . -name "*.bak" -exec rm {} \;`*
7. **Find the file with exact permissions `700`.** (Should find `backup.tar.gz`).
