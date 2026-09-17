# Mastering `curl`

`curl` is a command-line tool for transferring data over various network protocols (most commonly HTTP and HTTPS). It is the backbone of API testing and shell scripting when you need to interact with the web.

## 1. Basic Requests (GET)

By default, `curl` performs an HTTP GET request and prints the response body (usually HTML or JSON) directly to your terminal.

```bash
curl https://example.com
```

## 2. Downloading Files

If you want to save the output to a file instead of printing it to the terminal:

**Save with the original filename:** Use `-O` (uppercase O).
```bash
curl -O https://example.com/image.png
```
*(This saves the file as `image.png` in your current directory).*

**Save with a custom filename:** Use `-o` (lowercase o).
```bash
curl -o my_download.html https://example.com
```

## 3. Following Redirects

Often, URLs redirect to a new location (e.g., HTTP redirects to HTTPS). By default, `curl` does *not* follow redirects. Use `-L` (Location) to tell it to follow them.

```bash
curl -L http://github.com
```

## 4. Viewing Headers

Headers contain metadata about the response (status code, content type, cookies, etc.).

**View ONLY the headers:** Use `-I` (capital i / HEAD request).
```bash
curl -I https://example.com
```

**View both headers AND the body:** Use `-i` (lowercase i).
```bash
curl -i https://example.com
```

## 5. Changing the HTTP Method

By default, `curl` uses GET. You can change this using `-X` (although it's sometimes implied by other flags).

```bash
curl -X DELETE https://api.example.com/users/123
```

## 6. Sending Data (POST/PUT Requests)

To send data, use the `-d` (data) flag. When you use `-d`, `curl` automatically changes the method to POST.

**Sending form data:**
```bash
curl -d "username=admin&password=123" https://api.example.com/login
```

**Sending JSON data:**
APIs usually require JSON. You must set the `Content-Type` header using `-H` so the server knows how to parse it.

```bash
curl -X POST https://api.example.com/users \
     -H "Content-Type: application/json" \
     -d '{"name": "Alice", "role": "admin"}'
```

## 7. Sending Custom Headers

Use `-H` to add any custom headers, like authorization tokens.

```bash
curl -H "Authorization: Bearer my_secret_token" https://api.example.com/protected
```

## 8. Insecure Connections

If you are testing a local server with a self-signed certificate, `curl` will throw an SSL error. Use `-k` (or `--insecure`) to bypass certificate validation.

```bash
curl -k https://localhost:8443
```

## 9. Silent Mode

`curl` usually prints a progress meter when downloading or outputting to a file. Use `-s` (silent) to hide this. This is very useful in scripts.

```bash
curl -s -O https://example.com/large_file.zip
```

---

## Exercises

**Exercise 1: Basic Download**
Download the HTML of `https://google.com` and save it to a file named `google.html` using the lowercase `-o` flag.

**Exercise 2: Inspecting Headers**
Run a command to fetch *only* the headers of `https://github.com`. Look at the `HTTP/2` status code at the top.

**Exercise 3: Following Redirects**
Try running `curl -I http://google.com` (notice the `http://` instead of `https://`). Look at the `Location:` header in the response, which tells you where it wants to redirect you. Now, add the flag to make `curl` follow that redirect automatically.

**Exercise 4: Making an API Request**
Use `curl` to fetch a random joke from an open API. Run:
`curl -H "Accept: application/json" https://icanhazdadjoke.com/`
(Notice how `-H` is used to tell the server you want JSON back instead of HTML).

**Exercise 5: Sending JSON (POST)**
Construct a `curl` command to send a POST request to `https://httpbin.org/post`. Send a JSON body containing `{"hello": "world"}` and make sure to include the correct `Content-Type` header. `httpbin.org` will echo back what it received!
