# Awk Tutorial

`awk` is a complete text-processing programming language. It processes files line by line, splitting each line into fields (columns).

## Basic Syntax
`awk 'pattern { action }' filename`

## Key Concepts
- `$0` : Represents the entire line.
- `$1, $2, $3...` : Represents the 1st, 2nd, 3rd fields (columns) respectively.
- `-F` : Field separator. By default, `awk` splits on whitespace. Use `-F","` for CSV files.
- `NR` : Number of Records (current line number).
- `NF` : Number of Fields (number of columns in the current line).
- `BEGIN { ... }` : Action to execute BEFORE processing the file (e.g., printing headers).
- `END { ... }` : Action to execute AFTER processing the file (e.g., printing totals).

## Examples
- Print columns 1 and 3: `awk '{ print $1, $3 }' file.txt`
- Print lines where column 3 is > 50: `awk '$3 > 50 { print $0 }' file.txt`

---

## Exercises (Use `sales_data.csv` - remember to use `-F","`)

1. **Print only the Names (Column 1) and Sales (Column 4)**.
2. **Print the details of employees in the "Engineering" department only**.
   *Hint: `awk -F"," '$3 == "Engineering" { print $0 }' sales_data.csv`*
3. **Print employees whose sales are greater than $50,000**.
   *Hint: `awk -F"," '$4 > 50000 { print $1, $4 }' sales_data.csv`*
4. **Calculate and print the total sales of all employees**.
   *Hint: Use a variable in the action block like `{ sum += $4 }`, then use `END { print sum }`.*
5. **Print line numbers alongside the records**.
   *Hint: Print `NR` before `$0`.*
6. **Print lines where the last name starts with "S"**.
   *Hint: Use regular expression matching on the name field: `$1 ~ / S/` or `awk -F"," '$1 ~ /.* S.*/'`*
