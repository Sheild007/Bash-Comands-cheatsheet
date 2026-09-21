# Shell Scripting Exercises

## 1 & 2. File Check Script and Permissions
**Script:** I've created the script at `exercises/check.sh`.
```bash
#!/usr/bin/env bash

if [ -z "$1" ]; then
    echo "Usage: $0 <filename>"
    exit 1
fi

if [ -f "$1" ]; then
    echo "File '$1' exists."
else
    echo "File '$1' does not exist."
fi
```
**Why `chmod +x` is necessary:**
By default, new files do not have the executable (`x`) permission bit set for safety reasons. Running `./check.sh` tells the OS to execute the file as a program. Without the execute permission (visible via `ls -l` as `rw-r--r--`), the OS will return a "Permission denied" error. Running `chmod +x check.sh` changes the permissions to allow execution (`rwxr-xr-x`).

## 3. The `set -x` flag
Adding `set -x` to a script enables a debugging mode (also known as "xtrace"). In this mode, the shell prints each command and its arguments to standard error (stderr) *after* parameter expansion, command substitution, and arithmetic expansion, but *before* the command is actually executed. It is incredibly useful for debugging scripts to see exactly what the shell is doing line by line.

## Part 2: SSH Exercises

### 1. Generate SSH Keys
To generate a secure `ed25519` key pair with a passphrase:
```bash
ssh-keygen -a 100 -t ed25519
```
*(Press enter to accept the default path `~/.ssh/id_ed25519` and make sure to type a strong passphrase).*

### 2. Configure `~/.ssh/config`
Edit your SSH config file (e.g., `nano ~/.ssh/config`) to include an entry for your VM. Replace `username_goes_here` and `ip_goes_here` with your VM's actual details:
```text
Host vm
    User username_goes_here
    HostName ip_goes_here
    IdentityFile ~/.ssh/id_ed25519
    LocalForward 9999 localhost:8888
```

### 3. Copy the Key to the Server
Copy your newly generated public key to the VM so you can log in securely:
```bash
ssh-copy-id vm
```

### 4. Port Forwarding & Webserver Test
1. SSH into the VM: `ssh vm`
2. Start a python webserver on the VM on port 8888: 
   ```bash
   python -m http.server 8888
   ```
3. Open a browser on your *local machine* and navigate to `http://localhost:9999`. The `LocalForward` config will securely tunnel this port through SSH to the VM's port 8888!

### 5. Secure the SSH Server (On the VM)
Edit the SSH daemon config file on the VM to harden security:
```bash
sudo vim /etc/ssh/sshd_config
```
Change these values (uncomment them if they have a `#` in front):
```text
PasswordAuthentication no
PermitRootLogin no
```
Save and restart the SSH service on the VM:
```bash
sudo service sshd restart
```
Log out and try `ssh vm` again to ensure your key still works.

### Challenge 1: Mosh (Mobile Shell)
1. Install mosh on both your local machine and the VM.
2. Connect using mosh: `mosh vm`
3. If you disconnect your network adapter (turn off WiFi, etc.) and turn it back on, mosh will automatically recover the session without dropping it!

### Challenge 2: Background Port Forwarding
If you just want to set up the port forward without opening an interactive shell session, use the `-N` and `-f` flags:
- `-N`: Do not execute a remote command (just forward ports).
- `-f`: Requests SSH to go to the background just before command execution.
```bash
ssh -N -f vm
```
## 4. Copy to backup with today's date
```bash
cp notes.txt "notes_$(date +%Y-%m-%d).txt"
```
*Hint:* `$(...)` evaluates the command inside and substitutes its output. `date +%Y-%m-%d` outputs the current date in YYYY-MM-DD format.

## 5. Modify flaky test script
**Script:** I've created the script at `exercises/flaky_test.sh`.
By using `$@` (all arguments passed to the script), the script can execute any command instead of a hardcoded one. E.g., `./flaky_test.sh cargo test my_test`.

## 6. Top 5 most common file extensions in your home directory
```bash
find ~ -type f 2>/dev/null | awk -F. '{if (NF>1) print $NF}' | sort | uniq -c | sort -nr | head -n 5
```
**Explanation:** 
- `find ~ -type f` finds all files in the home directory.
- `awk -F. '{if (NF>1) print $NF}'` uses `.` as a delimiter and prints the last field (the extension) only if a dot exists.
- `sort` sorts the extensions alphabetically so `uniq` can count them.
- `uniq -c` counts adjacent identical lines.
- `sort -nr` sorts numerically in descending order.
- `head -n 5` takes the top 5.

## 7. Find all `.sh` files and count lines using `xargs`
```bash
find . -type f -name "*.sh" -print0 | xargs -0 wc -l
```
**Explanation:** 
- `-print0` tells `find` to separate filenames with a null character (`\0`) instead of a newline.
- `-0` tells `xargs` to expect null-separated input. This combination correctly handles filenames with spaces, newlines, or other special characters.

## 8. Count lectures on MIT Missing Semester course website
```bash
curl -s https://missing.csail.mit.edu/ | grep -o 'href="/[0-9]\{4\}/[^/]\+/"' | wc -l
```
**Explanation:** 
- `curl -s` fetches the HTML silently.
- `grep -o` extracts only the matched pattern. The pattern `href="/[0-9]\{4\}/[^/]\+/"` matches the lecture links format (e.g., `href="/2026/course-shell/"`).
- `wc -l` counts the number of matches.

## 9. Extract names from JSON using `jq`
```bash
curl -s https://microsoftedge.github.io/Demos/json-dummy-data/64KB.json | jq '.[] | select(.version > 6) | .name'
```
**Explanation:** 
- `curl -s` fetches the JSON payload.
- `jq '.[]'` iterates over the top-level array.
- `select(.version > 6)` filters the objects where the version is greater than 6.
- `.name` extracts only the `name` property from the filtered objects.

## 10. `awk` column manipulation
```bash
printf 'a 50 x\nb 150 y\nc 200 z\n' | awk '$2 > 100 { print $3, $2, $1 }'
```
**Explanation:** 
- `$2 > 100` is the condition (matches if the second column is greater than 100).
- `{ print $3, $2, $1 }` prints the 3rd, 2nd, and 1st columns in that order, effectively swapping the 1st and 3rd columns and dropping any subsequent columns if they existed.

## 11. SSH log pipeline and Bash History pipeline

### Dissecting the SSH log pipeline:
```bash
journalctl | grep sshd | grep "Disconnected from" | sed -E 's/.*Disconnected from (invalid |authenticating )?user (.*) [^ ]+ port [0-9]+( \[preauth\])?$/\2/' | sort | uniq -c | sort -nk1,1 | tail -n10 | awk '{print $2}'
```
1. `journalctl`: Outputs systemd journal logs.
2. `grep sshd`: Filters logs to include only SSH daemon entries.
3. `grep "Disconnected from"`: Filters for disconnection events.
4. `sed -E '...'`: Uses a capture group `\2` to isolate just the username from the log line format.
5. `sort`: Sorts usernames alphabetically (required before `uniq`).
6. `uniq -c`: Counts consecutive identical usernames.
7. `sort -nk1,1`: Sorts numerically (`-n`) based on the first column (`-k1,1`), which is the count.
8. `tail -n10`: Takes the bottom 10 lines (the ones with the highest counts).
9. `awk '{print $2}'`: Prints only the 2nd column (the username), discarding the counts.

### Most-used shell commands from history:
```bash
cat ~/.bash_history | awk '{print $1}' | sort | uniq -c | sort -nr | head -n 10
```
**Explanation:** 
- `cat ~/.bash_history`: Reads the bash history file.
- `awk '{print $1}'`: Extracts the first word (the command) from each line.
- `sort`: Alphabetical sort.
- `uniq -c`: Counts occurrences of each command.
- `sort -nr`: Sorts numerically descending by count.
- `head -n 10`: Grabs the top 10 most used commands.
*(Note for Zsh users: you may need to strip timestamps first with `sed -E 's/^: [0-9]+:[0-9]+;//'`)*

## Part 3: Profiling and Benchmarking Exercises

### 1. `perf stat`
Run `perf stat ls` (or any other command).
**What do the counters mean?**
- `task-clock`: How much CPU time the task took in total across all cores.
- `context-switches`: Times the CPU switched from this task to another (due to interrupts, blocking, etc.).
- `cpu-migrations`: Times the task moved from one CPU core to another.
- `page-faults`: Times the OS had to fetch memory from disk/RAM that wasn't immediately available.
- `cycles`: Total CPU cycles consumed.
- `instructions`: Total CPU instructions executed (IPC = instructions per cycle, higher is better).
- `branches` & `branch-misses`: Total conditional branches and how often the CPU guessed the wrong execution path.

### 2. `perf record` and Flame Graphs
I created `slow.c` in the `profiling` directory for you.
```bash
# Compile
gcc -g -O2 slow.c -o slow -lm
# Record execution
perf record -g ./slow
# View report
perf report
```
**Flame Graph Generation:**
```bash
git clone https://github.com/brendangregg/FlameGraph
perf script > out.perf
./FlameGraph/stackcollapse-perf.pl out.perf > out.folded
./FlameGraph/flamegraph.pl out.folded > profile.svg
```

### 3. Benchmarking with `hyperfine`
Benchmarking `find` vs `fd`:
```bash
hyperfine "find . -name '*.md'" "fd -e md"
```
*(You will see that `fd` is significantly faster!)*

### 4. `taskset` and `stress`
Command: `taskset --cpu-list 0,2 stress -c 3`
**Why doesn’t stress use three CPUs?**
The `-c 3` flag tells `stress` to spawn 3 workers spinning on `sqrt()`. However, `taskset --cpu-list 0,2` restricts the *entire process and all its children* to only ever run on CPU cores 0 and 2. Therefore, those 3 workers are forced to share just 2 CPU cores, meaning it can never utilize a 3rd core, no matter how many workers you spawn!

### 5. Port Discovery with `ss`
```bash
# Start server in background
python3 -m http.server 4444 &

# Find the PID listening on 4444
ss -tlnp | grep 4444

# Output looks something like this (the PID is 12345):
# LISTEN 0 50 0.0.0.0:4444 0.0.0.0:* users:(("python3",pid=12345,fd=3))

# Terminate it
kill 12345
```

## Part 4: Environments, Packages, and Docker

### 1. Virtual Environments and `$PATH`
**What changed in the environment?** 
When you activate a virtual environment, the shell prepends the venv's `bin` directory to your `$PATH` environment variable. It also sets variables like `$VIRTUAL_ENV`.
**Why does the shell prefer the venv?** 
Because the venv's `bin` directory is added to the *beginning* of `$PATH`. When you type `python`, the shell searches directories in `$PATH` from left to right. It finds the Python binary in the venv first, so it uses that one instead of the system Python.
**What does `deactivate` do?** 
If you run `type deactivate`, you'll see it's a shell function (not a script). It undoes the changes made during activation: it removes the venv's `bin` directory from `$PATH`, unsets `$VIRTUAL_ENV`, and restores your original command prompt.

### 2. Python Package and Lockfile
I have created a sample package skeleton in the `python_package/` directory with a `pyproject.toml`.
To install it in a venv and generate a lockfile (using `pip-tools`):
```bash
cd python_package
python -m venv venv
source venv/bin/activate
pip install pip-tools
# Compile a lockfile from pyproject.toml
pip-compile pyproject.toml
# Inspect the lockfile
cat requirements.txt
# Install from lockfile
pip-sync
```

### 3. Build Missing Semester Website with Docker
```bash
git clone https://github.com/missing-semester/missing-semester.git
cd missing-semester
# Build and run the docker container in the background
docker compose up -d
# View the website at http://localhost:4000
```

### 4. Dockerfile & Docker Compose (Python + Redis)
I have created a complete working example in the `python_docker_app/` directory!
It contains:
- `app.py`: A simple python web server that increments a counter in Redis.
- `Dockerfile`: Instructions to build the Python app.
- `docker-compose.yml`: Wires the Python app container and a Redis container together.
To run it:
```bash
cd python_docker_app
docker compose up
# Then visit http://localhost:8000
```

### 5. Publishing to TestPyPI & ghcr.io
**Publishing to TestPyPI:**
```bash
cd python_package
pip install build twine
python -m build
# Upload to TestPyPI (requires an account and API token)
python -m twine upload --repository testpypi dist/*
```
**Pushing a Docker image to GitHub Container Registry (ghcr.io):**
```bash
# Login using a GitHub Personal Access Token (PAT)
echo $CR_PAT | docker login ghcr.io -u YOUR_GITHUB_USERNAME --password-stdin
# Tag the image
docker tag my-python-app ghcr.io/your_github_username/my-python-app:latest
# Push the image
docker push ghcr.io/your_github_username/my-python-app:latest
```

### 6. GitHub Pages
1. Go to your GitHub repository settings.
2. Under the "Pages" tab, select the "main" branch and save.
3. GitHub will automatically host your `README.md` (or any `index.html`) at `https://yourusername.github.io/Bash-Comands-cheatsheet/`.
*(To configure a custom domain, you would add a `CNAME` file to the root of the repo with your domain name, and configure your DNS provider with a CNAME record pointing to `yourusername.github.io`)*.
