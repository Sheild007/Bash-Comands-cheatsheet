# Mastering `jq`

`jq` is a lightweight and flexible command-line JSON processor. It is like `sed` for JSON data – you can use it to slice, filter, map, and transform structured data with ease.

## 1. Pretty-Printing

If you have an unformatted, minified JSON response (often from `curl`), you can use `jq` just to make it readable. The `.` (dot) filter simply takes the input and outputs it unchanged (but pretty-printed).

```bash
# Pretty-print a JSON string
echo '{"name":"Alice","role":"admin"}' | jq '.'

# Pretty-print an API response
curl -s https://api.github.com/users/octocat | jq '.'
```

## 2. Accessing Object Properties

Use `.key_name` to extract the value of a specific key.

```bash
echo '{"user": {"name": "Bob", "id": 123}}' | jq '.user.name'
# Output: "Bob"
```

If a key contains spaces or special characters, wrap it in quotes:
```bash
echo '{"first name": "Charlie"}' | jq '.["first name"]'
```

## 3. Accessing Arrays

You can extract elements from an array by index, just like in programming.

```bash
echo '["apple", "banana", "cherry"]' | jq '.[1]'
# Output: "banana"
```

**Iterating over an array:**
Use `.[]` to return all elements of an array as separate, individual results (a stream).

```bash
echo '[{"id": 1}, {"id": 2}]' | jq '.[]'
# Output:
# {
#   "id": 1
# }
# {
#   "id": 2
# }
```

## 4. Piping Filters (`|`)

You can chain `jq` filters together using the pipe `|` operator inside your `jq` string. This allows you to combine array iteration with property access.

```bash
echo '[{"name": "Alice"}, {"name": "Bob"}]' | jq '.[] | .name'
# Output:
# "Alice"
# "Bob"
```

## 5. Constructing New JSON

You can use `jq` to build entirely new JSON structures from the data you're parsing.

**Creating Arrays (`[]`):**
```bash
# Wrap the output back into an array
echo '[{"name": "Alice"}, {"name": "Bob"}]' | jq '[.[] | .name]'
# Output: ["Alice", "Bob"]
```

**Creating Objects (`{}`):**
```bash
# Map old keys to new keys
echo '{"first": "Alice", "last": "Smith"}' | jq '{fullName: (.first + " " + .last)}'
# Output: { "fullName": "Alice Smith" }
```

## 6. Filtering Data (`select`)

Use `select(condition)` to filter array elements that meet a certain criteria.

```bash
echo '[{"name": "Alice", "admin": true}, {"name": "Bob", "admin": false}]' | \
jq '.[] | select(.admin == true) | .name'
# Output: "Alice"
```

## 7. Useful Flags

- **`-r` (raw output):** By default, `jq` outputs strings enclosed in quotes (e.g., `"Alice"`). If you want to use the output in a bash script variable, you usually want the raw string without quotes. Use `-r`.
```bash
NAME=$(echo '{"name": "Alice"}' | jq -r '.name')
echo "Hello $NAME" # Outputs: Hello Alice
```
- **`-c` (compact):** Outputs the JSON as a single minified line, useful for piping into other tools.

## Exercises

**Exercise 1: Pretty Printing**
Use `curl` in silent mode (`-s`) to fetch data from `https://jsonplaceholder.typicode.com/todos/1` and pipe it into `jq '.'` to see the pretty-printed result.

**Exercise 2: Property Access**
Modify the command from Exercise 1 to only output the title of the todo item (hint: use `.title`).

**Exercise 3: Array Iteration**
Fetch the list of all users from `https://jsonplaceholder.typicode.com/users`. Use `jq` to iterate through the array and extract only the `email` of each user.

**Exercise 4: Raw Output**
Modify the command from Exercise 3 to output raw strings (using the `-r` flag) so that the emails print without double quotes around them.

**Exercise 5: Filtering with Select**
Fetch the list of all todos from `https://jsonplaceholder.typicode.com/todos`. Filter the array using `select` to only find items where `completed` is `true`.
