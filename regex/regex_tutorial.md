# Regex (Regular Expressions) Tutorial

Regular Expressions (regex) are patterns used to match character combinations in strings. 
They are heavily used in `grep`, `sed`, `awk`, and programming languages.

## Key Concepts

### 1. Anchors
- `^` : Matches the start of a line. (e.g., `^Hello` matches "Hello" at the beginning)
- `$` : Matches the end of a line. (e.g., `world$` matches "world" at the end)

### 2. Character Classes
- `.` : Matches ANY single character (except newline).
- `[abc]` : Matches any one character inside the brackets (a, b, or c).
- `[^abc]` : Matches any character NOT inside the brackets.
- `[a-z]`, `[0-9]` : Matches ranges (lowercase letters, digits).
- `\d` : Matches a digit (same as `[0-9]`).
- `\w` : Matches a word character (alphanumeric + underscore).
- `\s` : Matches whitespace (spaces, tabs).

### 3. Quantifiers
- `*` : Matches 0 or more occurrences of the preceding element.
- `+` : Matches 1 or more occurrences (requires extended regex, e.g., `grep -E`).
- `?` : Matches 0 or 1 occurrence (optional).
- `{n}` : Matches exactly *n* occurrences.
- `{n,m}` : Matches between *n* and *m* occurrences.

### 4. Grouping & Alternation
- `(abc)` : Capturing group. Treats "abc" as a single unit.
- `cat|dog` : Alternation (OR). Matches "cat" OR "dog".
- `\` : Escape character. Use `\.` to match a literal period.

---

## Exercises (Use `grep -E` to test these on `regex_practice.txt`)

1. **Find all phone numbers**: (Format: `XXX-XXX-XXXX`)
   *Hint: Use digits and hyphens.*
2. **Find all valid email addresses**:
   *Hint: Look for word characters, an `@` symbol, more word characters, a `.`, and a domain.*
3. **Find all lines starting with "Error"**:
   *Hint: Use an anchor.*
4. **Find all IPv4 addresses**: (Format: `X.X.X.X` where X is 1-3 digits)
   *Hint: Remember to escape the dot `\.`*
5. **Find dates in the format `YYYY-MM-DD`**:
