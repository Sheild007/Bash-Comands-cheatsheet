# Mastering SSH (Secure Shell) & SCP

SSH is the standard way to securely connect to remote servers. This guide covers basic usage, key generation, advanced port forwarding, and more.

## 1. Basic Connection

Connect to a remote server using a username and hostname (or IP).
```bash
ssh user@hostname_or_ip
```
To connect on a specific port (default is 22):
```bash
ssh -p 2222 user@hostname
```

## 2. SSH Keys (Passwordless Login)

SSH keys are more secure and convenient than passwords.

**Generate a Key Pair:**
```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```
This creates a private key (`~/.ssh/id_ed25519`) and a public key (`~/.ssh/id_ed25519.pub`). **Never share your private key.**

**Copy the Public Key to the Server:**
Use `ssh-copy-id` to easily append your public key to the server's `~/.ssh/authorized_keys` file.
```bash
ssh-copy-id user@hostname
```
Now you can `ssh user@hostname` without a password!

## 3. Port Forwarding (Tunnels)

Port forwarding routes local network traffic to remote systems securely over SSH.

### Local Port Forwarding (`-L`)
Forwards a local port to a remote destination.
*Syntax: `-L local_port:destination_host:destination_port`*

Example: Accessing a remote database (running on port 5432) on your local machine.
```bash
ssh -L 8080:localhost:5432 user@hostname
```
Now, connecting to `localhost:8080` locally actually connects to `localhost:5432` on the remote server.

### Remote Port Forwarding (`-R`)
Forwards a remote port to a local destination. (Exposing a local service to the remote server).
*Syntax: `-R remote_port:destination_host:destination_port`*

Example: Exposing your local dev server (port 3000) to the remote server.
```bash
ssh -R 9000:localhost:3000 user@hostname
```
Now, someone on the remote server can curl `localhost:9000` to hit your laptop's port 3000.

### Dynamic Port Forwarding (`-D`)
Creates a SOCKS proxy.
```bash
ssh -D 1080 user@hostname
```
You can configure your browser to use `localhost:1080` as a SOCKS5 proxy, routing all your web traffic securely through the remote server.

## 4. SCP: Secure Copy

`scp` uses SSH to copy files between machines.

**Local to Remote:**
```bash
scp /path/to/local_file.txt user@hostname:/path/to/remote_dir/
```

**Remote to Local:**
```bash
scp user@hostname:/path/to/remote_file.txt /path/to/local_dir/
```

**Copying Directories (Recursive):**
Use `-r`.
```bash
scp -r /local/dir/ user@hostname:/remote/dir/
```

## 5. SSH with Pipes

You can pipe data directly over an SSH connection without creating intermediate files.

**Pipe Local Data to a Remote File:**
```bash
cat local_data.sql | ssh user@hostname "cat > remote_data.sql"
```

**Pipe Remote Data to a Local Command:**
```bash
ssh user@hostname "cat /var/log/syslog" | grep "ERROR"
```
This reads the remote syslog but runs `grep` on your local CPU!

**Run a Local Script on a Remote Machine:**
```bash
ssh user@hostname 'bash -s' < local_script.sh
```

## 6. SSH Config File (`~/.ssh/config`)

You can save connection details to avoid typing them every time. Create or edit `~/.ssh/config`:
```text
Host myserver
    HostName 192.168.1.100
    User usmandauna
    Port 2222
    IdentityFile ~/.ssh/id_ed25519
```
Now you can simply type `ssh myserver` to connect!

## Exercises

**Exercise 1: Key Gen**
Generate a new `ed25519` key pair (name it `test_key` when prompted, instead of the default, so you don't overwrite anything). Look at the public key using `cat`.

**Exercise 2: SSH Config**
Create a block in `~/.ssh/config` for a fictional server `db-prod` pointing to IP `10.0.0.50`, user `admin`.

**Exercise 3: Piping**
Write a command that tars and gzips a local directory and pipes the compressed stream directly via SSH to a remote server to be extracted. (Hint: `tar czf - ./dir | ssh user@host "tar xzf - -C /dest"`)
